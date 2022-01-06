//
// Created by Robert Koziarski on 14.11.2021.
//

#include "model.h"

// Allocates memory and loads data from the .json file passed into the constructor
// Assumes a file format equivalent to the one generated from data_gen.py script included in the package
void Model::loadModel(const std::string& file_path) {
    json json_file = R"({"n": 20,"m": 6,"prices": [5, 26, 16, 13, 17, 8],"quantities": [100, 100, 300, 400, 100, 200],"dates": [5, 3, 4, 3, 1, 3],"recipes": [[134, 118, 187, 113, 133, 162], [123, 161, 185, 113, 131, 163], [101, 150, 178, 110, 166, 104], [186, 101, 191, 170, 164, 126], [174, 118, 138, 117, 167, 101], [134, 194, 115, 153, 190, 103], [102, 187, 124, 166, 124, 150], [184, 159, 185, 126, 170, 155], [161, 196, 116, 105, 180, 170], [157, 157, 123, 190, 159, 159], [126, 100, 185, 127, 162, 146], [164, 167, 191, 136, 172, 103], [118, 184, 156, 153, 160, 125], [104, 132, 127, 185, 143, 105], [133, 119, 179, 118, 104, 182], [145, 112, 167, 173, 151, 156], [199, 107, 125, 130, 129, 109], [195, 171, 130, 182, 178, 188], [119, 136, 128, 111, 191, 129], [149, 173, 155, 123, 159, 132]],"times": [8, 16, 15, 28, 14, 30, 25, 26, 9, 9, 22, 17, 27, 21, 12, 26, 21, 6, 20, 31]})"_json;

    m_n = json_file["n"];
    m_m = json_file["m"];

    // TODO: figure out how big should the solution space be
//    m_X.reserve(m_n);
//    for(auto& solution : m_X) {
//        solution.reserve(m_p);
//    }
    today = 1;
    money = 1000;
    m_R = json_file["recipes"].get<std::vector<std::vector<int>>>();
    m_T = json_file["times"].get<std::vector<int>>();
    m_Q = json_file["quantities"].get<std::vector<int>>();
    m_E = json_file["dates"].get<std::vector<int>>();
    m_P = json_file["prices"].get<std::vector<int>>();

    params = CostFunctionParams(1.0, 1.0, 1.0);
}

void Model::set_params(double a, double b, double g) {
    params = CostFunctionParams(a, b, g);
}

int Model::get_solution_space_size() const {
    return m_X.size();
}

double Model::testCostFunction(int solution_nr) {
    // generates one solution and calculates the cost function
    if (m_X.empty()) generateAllBinaryPerm();
    return calculateCostFunction(solution_nr);
}

inline bool Model::determineIsProductExpired(int product_idx) const {
    return m_T[product_idx] < today;
}

double Model::calculateCostFunction(int p_solution) const {
    double cost_shop = 0;
    double cost_loss = 0;
    double cost_time = 0;

    const auto& solution = m_X[p_solution];

    for (int j = 0; j < m_n; ++j) {
        if (!solution[j]) continue;
        const auto& recipe = m_R[j];
        cost_time += m_T[j];
        for (int i = 0; i < m_m; ++i) {
            // update shop cost
            cost_shop += (double) m_P[i] * MAX(0, m_Q[i] - recipe[j]);
            // update loss cost
            cost_loss += (double) m_P[i] * determineIsProductExpired(i) * MAX(0, recipe[j] - m_Q[i]);
        }
    }

    return params.alpha * cost_shop + params.beta * cost_loss + params.gamma * cost_time;
}

std::pair<double, int> Model::tabooSearch(int max_iterations, double asp_coeff = 1.0) {
    aspiration_coefficient = asp_coeff;
    iteration_limit = max_iterations;

    best_min = 9999999.0;
    int best_idx = -1;
    // 1. how to store moves? It should be stored as a vector containing a map with changes from 0 to 1 or 1 to 0 on certain index
    // (vector[0] = (-1) -> move is allowed
    // (vector[0] = (0) -> don't allow to change 0 to 1 on 1st element)
    // (vector[0] = (1) -> dont' allow to change 1 to 0 on 1st elemnt)
    // 2. how to use the taboo list? we check if vector[0] is 0 (false) and
    // 3. how to implement the below -> I think it's pretty straight forward once we know how to use the taboo list
    // 4. how to add to taboo list
    /*

     for(solution : non-taboo-neighbors)
        if solution-score > best-current-score:
            best-current = solution

     for(solution : taboo-neighbors)
        if solution-score > global-best-score:
            untaboo(solution)
            best-current = solution

     update-score()

     */

    generateAllBinaryPerm();

    double current_best = 9999999999999.0;
    int current_idx = -1;
    int idx_taboo_remove;

    for (int i = 0; i < m_X.size(); ++i) {
        if(random_bool()) {
            non_taboo.push_back(i);
        } else {
            Taboo new_taboo{};
            new_taboo.idx = i;
            taboo_list.push_back(new_taboo);
        }
    }

    while (iteration_limit--) {

        // choose the best admissible candidate
        for(int solution_idx : non_taboo) {
            double tmp_score = calculateCostFunction(solution_idx);
            if (tmp_score < current_best) {
                addNewToTaboo(current_idx, solution_idx);
                current_idx = solution_idx;
                current_best = tmp_score;
            }
        }

        // search taboo list for aspiration criterion
        for(int i = 0; i < taboo_list.size(); ++i) {
            idx_taboo_remove = -1;
            double tmp_score = calculateCostFunction(taboo_list[i].idx);
            if (tmp_score < aspiration_coefficient * best_min) {
                best_idx = taboo_list[i].idx;
                idx_taboo_remove = i;
                best_min = tmp_score;
            }
        }

        // remove the best solution from taboo list
        if (idx_taboo_remove >= 0 && idx_taboo_remove < taboo_list.size())
            taboo_list.erase(taboo_list.begin() + idx_taboo_remove);

    }
    return std::pair<double, int> {best_min, best_idx};
}

void Model::addNewToTaboo(int old_idx, int new_idx) {
    for (int i = 0; i < m_n; ++i) {
        if (old_idx == -1) {
            Taboo new_taboo{};
            new_taboo.idx = i;
            taboo_list.push_back(new_taboo);

        }
        else if (m_X[old_idx][i] != m_X[new_idx][i]) {
            Taboo new_taboo{};
            new_taboo.idx = i;
            new_taboo.move = ( m_X[old_idx][i] == 0 ? ZERO_ONE : ONE_ZERO );
            taboo_list.push_back(new_taboo);
        }
    }
}

//std::vector<bool> Model::generateSolutionDiff(std::vector<bool>& current, int diff) {
//    std::uniform_int_distribution<> random_idx(0, current.size());
//    std::set<int> indices;
//
//}

void Model::generateRandomSolution() {
    std::vector<bool> initial_solution;
    for (int i = 0; i < m_n; ++i) {
        initial_solution.push_back(random_bool());
    }
    m_X.push_back(initial_solution);
}

// generates n! solutions
void Model::generateAllBinaryPerm() {
    std::vector<bool> initial_solution;
    for (int i = 0; i < m_n; ++i) {
        if (i < 3) initial_solution.push_back(true);
        else initial_solution.push_back(false);
    }
    m_X.push_back(initial_solution);
    solutionPermute(initial_solution, m_n, 0);
}

void Model::solutionPermute(std::vector<bool> current, int n, int i) {
    if (i == n) {
        unsigned int vec_sum = std::count(current.begin(), current.end(), true);
        if (vec_sum == 3) m_X.push_back(current);
        return;
    }
    current[i] = false;
    solutionPermute(current, n, i + 1);

    current[i] = true;
    solutionPermute(current, n, i + 1);
}
