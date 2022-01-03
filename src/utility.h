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
#include "json.h"

/*
    TODO: figure out a better way to do this
 */

using json = nlohmann::json;

typedef std::vector<std::vector<int>> Matrix2;
typedef std::vector<std::vector<bool>> Matrix2Bool;
typedef std::vector<int> VectorInt;
typedef std::vector<bool> VectorBool;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::bernoulli_distribution randomBoolGenerator(0.5); // 50% for true and 50% for false

static std::string menu_str = "Menu\n======================\n1. File input\n2. Parameter selection\n3. Result view\n4. Optimize\nInput: ";
static std::string file_sel_str = "File input\n======================\n";
static std::string param_sel_str = "Parameter selection\n======================\n";
static std::string result_view_str = "Result view\n======================\n";
static std::string calculations_str = "Performing optimization...\n";
static std::string quit_str = "Quitting...";

std::vector<std::string> strSplit(std::string& str, char delim);
std::vector<bool> randomSolution(std::size_t size);

struct CostFunctionParams {
    explicit CostFunctionParams(double a=1.0, double b=1.0, double g=0.0);
    double alpha;
    double beta;
    double gamma;
};

enum AppState {
    MENU,
    FILE_SEL,
    PARAM_SEL,
    RESULT_VIEW,
    CALCULATIONS,
    QUIT
};

#endif //OPERATIONALRESEARCHAPP_UTILITY_H
