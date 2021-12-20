//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_UTILITY_H
#define OPERATIONALRESEARCHAPP_UTILITY_H

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>
#include <set>
#include <random>
#include <functional>
#include <ctime>

/*
    TODO: figure out a better way to do this
 */
static std::random_device rd;
static std::mt19937 gen(rd());
static std::bernoulli_distribution randomBoolGenerator(0.5); // 50% for true and 50% for false

std::vector<std::string> strSplit(std::string& str, char delim);
std::vector<bool> randomSolution(std::size_t size);

struct CostFunctionParams {
    explicit CostFunctionParams(double a=1.0, double b=1.0, double g=0.0);
    double alpha;
    double beta;
    double gamma;
};

#endif //OPERATIONALRESEARCHAPP_UTILITY_H
