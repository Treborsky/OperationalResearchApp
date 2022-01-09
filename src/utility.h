//
// Created by Robert Koziarski on 09.11.2021.
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
#include <limits>
#include <algorithm>
#include "json.h"

#define MAX(a, b) ((a > b) ? (a) : (b))

using json = nlohmann::json;

void clearConsole();

inline static std::function<bool()> random_bool = std::bind(std::uniform_int_distribution<>(0, 1), std::mt19937());

inline static const char * neighbourhood_select_menu = "1. Hamming 2\n2. Hamming 3\n3. Hamming 4\n4. Random\n";
inline static const char * ssm_select_menu = "1. Best cost function value\n2. Random\n";
//inline static const char * menu_str = "Menu\n======================\n1. File input\n2. Parameter selection\n3. Result view\n4. Optimize\nInput: ";
//inline static const char * file_sel_str = "File input\n======================\n";
//inline static const char * param_sel_str = "Parameter selection\n======================\n";
//inline static const char * result_view_str = "Result view\n======================\n";
//inline static const char * calculations_str = "Performing optimization...\n";

struct CostFunctionParams {
    explicit CostFunctionParams(double a=1.0, double b=1.0, double g=0.0);
    double alpha;
    double beta;
    double gamma;
};

enum Move {
    ZERO_ONE,
    ONE_ZERO
};

struct TabooList {
    TabooList() : size(0), full(false) {}

    [[nodiscard]] bool contains(int idx) const;
    void iterate();
    void add(int idx, Move mv, int memory_len);
    void remove(int idx);
    bool operator[] (int idx) { return list_[idx] == ZERO_ONE; } // returns true if a 1 one is under idx

    // TODO: implement iterators for faster looping trough taboo list

    std::map<int, Move> list_;
    std::map<int, int> age_;

    int size;
    bool full;
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
