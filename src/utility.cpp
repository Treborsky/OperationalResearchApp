//
// Created by Robert Koziarski on 09.11.2021.
//

#include "utility.h"

void clearConsole() {
    std::cout << "\n========================================" << std::endl;
}

CostFunctionParams::CostFunctionParams(double a, double b, double g) { // normalization
    double sum = a + b + g;
    alpha = a / sum;
    beta = b / sum;
    gamma = g / sum;
}
