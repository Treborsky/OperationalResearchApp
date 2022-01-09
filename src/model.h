//
// Created by Robert Koziarski on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include "utility.h"  // TEMPORARY: pipelines will fail until I figure out a way to artifact the generated .json file


enum NeighborhoodType {
    HAM2 = 2,   // Hamming measure of value 2
    HAM3 = 3,   // ... 3
    HAM4 = 4,   // ... 4
    RAND,   // random generation
};

enum SolutionSelectionMethod {
    BEST,
    RANDOM,
};

// contains all data and functionality to perform
// optimization using the Taboo Search algo
class Model {
public:
    explicit Model(const std::string& = "../generated_data.json");
    std::pair<double, int> tabooSearch(int, NeighborhoodType, SolutionSelectionMethod, double, int);

    // setters / getters
    void set_params(double, double, double);
    void set_taboo_age(int, int, int);
private:
    // rng
    std::mt19937 rng;
    std::uniform_int_distribution<> dist;
    inline int rnd_idx();


    // solution generation - they update m_X, so no const qualifier
    std::vector<bool> generateInitial();
    std::vector<bool> generateNew(NeighborhoodType, const std::vector<bool>&);
    std::vector<std::vector<bool>> generateNewNeighborhood(NeighborhoodType, const std::vector<bool>&, int);

    [[nodiscard]] const double calculateCostFunction(const std::vector<bool>&) const;
    [[nodiscard]] inline bool determineIsProductExpired(int) const;

    int today;
    int money;
    std::vector<std::vector<int>> m_R;      // Recipe matrix (row = list of ingredients, row[i] = amount of certain ingredient
    std::vector<std::vector<bool>> m_X;  // Solution (row = one solution)
    std::vector<int> m_T;    // Times of preparation for recipes
    std::vector<int> m_Q;    // Amounts of ingredients
    std::vector<int> m_E;    // Expiration dates for ingredients
    std::vector<int> m_P;    // Prices for ingredients in the shop

    TabooList taboo_list; // contains indices inside a solution vector and a move that is taboo
    std::vector<int> non_taboo;    // has indices of solutions in m_X

    std::pair<int, double> global_best;
    int iteration_limit;
    double aspiration_coefficient;

    std::vector<double> best_X_sequence;

    int m_n;  // number of recipes
    int m_m;  // number of ingredients
    int m_p;  // size of solution space

    CostFunctionParams params;
    int taboo_age[3];
};

#endif //OPERATIONALRESEARCHAPP_MODEL_H
