//
// Created by User on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include "utility.h"

class Model {
public:
    void loadModel(const std::string& file_path);

private:
    void generateInitialSolution();
    void generateNewSolution();

    Matrix2 m_R;      // Recipe matrix (row = list of ingredients, row[i] = amount of certain ingredient
    Matrix2Bool m_X;  // Solution (row = one solution)
    VectorInt m_T;    // Times of preparation for recipes
    VectorInt m_Q;    // Amounts of ingredients
    VectorInt m_E;    // Expiration dates for ingredients
    VectorInt m_P;    // Prices for ingredients in the shop

    int m_n;  // number of recipes
    int m_m;  // number of ingredients
    int m_p;  // size of solution space
};

#endif //OPERATIONALRESEARCHAPP_MODEL_H
