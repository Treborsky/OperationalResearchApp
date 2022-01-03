//
// Created by User on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include "utility.h"

class Model {
public:
    void loadModel();
private:
    void loadRecipes();
    void loadTimes();
    void loadQuantities();
    void loadExpirationDates();
    void loadPrices();

    VectorBool generateInitialSolution();
    VectorBool generateNewSolution();

    Matrix2 R;      // Recipe matrix (row = list of ingredients, row[i] = amount of certain ingredient
    Matrix2Bool X;  // Solution (row = one solution)
    VectorInt T;    // Times of preparation for recipes
    VectorInt Q;    // Amounts of ingredients
    VectorInt E;    // Expiration dates for ingredients
    VectorInt P;    // Prices for ingredients in the shop

    const std::string data_file_path;

    int n;  // number of recipes
    int m;  // number of ingredients
    int p;  // size of solution space
}

#endif //OPERATIONALRESEARCHAPP_MODEL_H
