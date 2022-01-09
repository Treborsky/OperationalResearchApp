//
// Created by Robert Koziarski on 14.11.2021.
//

#include "model.h"

// Allocates memory and loads data from the .json file passed into the constructor
// Assumes a file format equivalent to the one generated from data_gen.py script included in the package
Model::Model(const std::string& file_path) {
#ifdef WIN32
    std::ifstream i(file_path, std::ios_base::binary);
#else
    std::ifstream i(file_path, std::ios_base::in);
#endif
    json json_file;
    i >> json_file;

    m_n = json_file["n"];
    m_m = json_file["m"];

    today = 1;
    money = json_file["money"];
    m_R = json_file["recipes"].get<std::vector<std::vector<int>>>();
    m_T = json_file["times"].get<std::vector<int>>();
    m_Q = json_file["quantities"].get<std::vector<int>>();
    m_E = json_file["dates"].get<std::vector<int>>();
    m_P = json_file["prices"].get<std::vector<int>>();

    params = CostFunctionParams(1.0, 1.0, 1.0);

    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<> (0, m_n-1);
}

void Model::set_params(double a, double b, double g) {
    params = CostFunctionParams(a, b, g);
}

inline bool Model::determineIsProductExpired(int product_idx) const {
    return m_T[product_idx] < today;
}

const double Model::calculateCostFunction(const std::vector<bool>& x) const {
    double cost_shop = 0;
    double cost_loss = 0;
    double cost_time = 0;

    for (int j = 0; j < m_n; ++j) {
        if (!x[j]) continue;
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

std::pair<double, int> Model::tabooSearch(int max_iterations, NeighborhoodType nbrhd_type,
                                          SolutionSelectionMethod ssm_type, double cutoff, int nbrhd_size) {
    // solution vector size = m_n
    // we need random
    // - bool for solutions (needn't be very fast - only the initial solution utilizes them)
    // - int (MUST be really fast - we decide the moves based on these generated indices)
    if (!m_X.empty()) m_X.clear();
    global_best.first = 0;

    std::vector<bool> s = generateInitial();
    global_best.second = calculateCostFunction(s);

    std::vector<std::vector<bool>> s_nbrhd;

    while (max_iterations--) {
        // generate neighborhood around current solution
        s_nbrhd = generateNewNeighborhood(nbrhd_type, s, nbrhd_size);
    }

    return global_best;
}

std::vector<bool> Model::generateInitial() {
    std::vector<bool> v;
    v.reserve(m_n);
    for (int i = 0; i < m_n; ++i) {
        v.push_back(random_bool());
    }

    m_X.push_back(v);

    return v;
}

// generates a new solution
// @param nbrhd_type - type of neighborhood (actually, type of generator)
// @param s          - solution to base the new solution on
// @returns x        - new solution
std::vector<bool> Model::generateNew(NeighborhoodType nbrhd_type, const std::vector<bool>& s) {    // todo: benchmark
    std::vector<bool> x = s;
    int idx;
    switch (nbrhd_type) {
        case HAM2:case HAM3:case HAM4:
            for (int i = 0; i < (int)nbrhd_type; ++i) { // interpret NeighbourHoodType as (int)
                while (taboo_list.contains(idx)) {
                    idx = rnd_idx();
                }
                x[idx] = !x[idx];
                taboo_list.add(idx, x[idx] ? ZERO_ONE : ONE_ZERO);
            }
            break;
        case RAND:
            for (int i = 0; i < m_n; ++i) { // todo: check if it's correct, because a random vector could acutally break taboo
                x[i] = random_bool();
                if (x[i] != s[i]) { // if a change occurred on ith place in the solution
                    // then we should check if it was taboo
                    if (!taboo_list.contains(i)) {  // if it doesn't, we add it
                        taboo_list.add(idx, x[idx] ? ZERO_ONE : ONE_ZERO);
                    } else { // if it does, then we change it back
                        x[i] = !x[i];
                    }
                }
            }
            break;
    } // here the solution generation should be already completed

    // add x to m_X and return
    m_X.push_back(x);

    return x;
}

// generates neighborhood around solution s
// @param type    - type of neighborhood to be generated
// @param s       - vector to generate the neighborhood around
// @param size    - size of the neighborhood
// @returns nbrhd - a neighborhood of size <size>
std::vector<std::vector<bool>> Model::generateNewNeighborhood(NeighborhoodType type, const std::vector<bool>& s, int size) {
    std::vector<std::vector<bool>> nbrhd;
    for (int i = 0; i < size; ++i) {
        nbrhd.push_back(generateNew(type, s));  // todo: checking for uniqueness -> we could somehow guarantee it in generateNew
    }
    return nbrhd;
}

inline int Model::rnd_idx() {
    return static_cast<int>(dist(rng));
}