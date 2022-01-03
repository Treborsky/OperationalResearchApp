//
// Created by Robert Koziarski on 09.11.2021.
//

#include "utility.h"


void clearConsole() {
    for (int i = 0; i < 500; i++) { std::cout << "\n"; }
}

CostFunctionParams::CostFunctionParams(double a, double b, double g) { // normalization
    double sum = a + b + g;
    alpha = a / sum;
    beta = b / sum;
    gamma = g / sum;
}

