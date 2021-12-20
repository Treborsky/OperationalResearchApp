//
// Created by User on 09.11.2021.
//

#include "utility.h"

std::vector<std::string> strSplit(std::string& str, char delim) {
    std::vector<std::string> tokens;
    tokens.reserve(30);     // completely arbitrary, doesn't affect the size
    std::string token;
    std::stringstream ss(str);
    while (ss.good()) {
        std::string sub;
        std::getline(ss, sub, delim);
        tokens.push_back(sub);
    }
    return tokens;
}

std::vector<bool> randomSolution(std::size_t size) {
    return std::vector<bool>;
}

CostFunctionParams::CostFunctionParams(double a, double b, double g) { // normalization
    double sum = a + b + g;
    alpha = a / sum;
    beta = b / sum;
    gamma = g / sum;
}