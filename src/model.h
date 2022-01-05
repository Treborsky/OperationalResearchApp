//
// Created by Robert Koziarski on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include "utility.h"

// contains all data and functionality to perform
// optimization using the Taboo Search algo
class Model {
public:
    void loadModel(const std::string& file_path);
    [[nodiscard]] double calculateCostFunction(int p_solution) const;
    std::pair<double, int> tabooSearch(int max_iterations, double asp_coeff);
    double testCostFunction(int solution_nr);
    void generateAllBinaryPerm();

    void set_params(double a, double b, double g);
    [[nodiscard]] int get_solution_space_size() const;
private:
    void addNewToTaboo(int old_idx, int new_idx);
    std::vector<bool> generateSolutionDiff(std::vector<bool>& current, int diff);
    void solutionPermute(std::vector<bool> current, int n, int i); // TODO: do it smarter
    void generateRandomSolution();
    [[nodiscard]] inline bool determineIsProductExpired(int product_idx) const;

    int today;
    int money;
    std::vector<std::vector<int>> m_R;      // Recipe matrix (row = list of ingredients, row[i] = amount of certain ingredient
    std::vector<std::vector<bool>> m_X;  // Solution (row = one solution)
    std::vector<int> m_T;    // Times of preparation for recipes
    std::vector<int> m_Q;    // Amounts of ingredients
    std::vector<int> m_E;    // Expiration dates for ingredients
    std::vector<int> m_P;    // Prices for ingredients in the shop

    std::vector<Taboo> taboo_list; // contains indices inside a solution vector and a move that is taboo
    std::vector<int> non_taboo;    // has indices of solutions in m_X
    double best_min;
    int iteration_limit;

    double aspiration_coefficient;
    int m_n;  // number of recipes
    int m_m;  // number of ingredients
    int m_p;  // size of solution space

    CostFunctionParams params;
};

#endif //OPERATIONALRESEARCHAPP_MODEL_H
