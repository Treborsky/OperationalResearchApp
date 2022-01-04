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
    m_R = json_file["recipes"].get<Matrix2>();
    m_T = json_file["times"].get<VectorInt>();
    m_Q = json_file["quantities"].get<VectorInt>();
    m_E = json_file["dates"].get<VectorInt>();
    m_P = json_file["prices"].get<VectorInt>();

    params = CostFunctionParams(1.0, 1.0, 1.0);
}

void Model::set_params(double a, double b, double g) {
    params = CostFunctionParams(a, b, g);
}

const int Model::get_solution_space_size() const {
    return m_X.size();
}


double Model::testCostFunction(int solution_nr) {
    // generates one solution and calculates the cost function
    generateInitialSolution();
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

void Model::generateInitialSolution() {
    VectorBool initial_solution;
    for (int i = 0; i < m_n; ++i) {
        initial_solution.push_back(randomBoolGenerator(gen));
    }
    m_X.push_back(initial_solution);
}

void Model::generateNewSolution() {
    // TODO: implement generating a new solution
}
