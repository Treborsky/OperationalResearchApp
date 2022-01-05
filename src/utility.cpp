//
// Created by Robert Koziarski on 09.11.2021.
//

#include "utility.h"

std::function<bool()> random_bool = std::bind(std::uniform_int_distribution<>(0, 1), std::mt19937());

//std::string menu_str = "Menu\n======================\n1. File input\n2. Parameter selection\n3. Result view\n4. Optimize\nInput: ";
//std::string file_sel_str = "File input\n======================\n";
//std::string param_sel_str = "Parameter selection\n======================\n";
//std::string result_view_str = "Result view\n======================\n";
//std::string calculations_str = "Performing optimization...\n";

void clearConsole() {
    std::cout << "\n========================================" << std::endl;
}

CostFunctionParams::CostFunctionParams(double a, double b, double g) { // normalization
    double sum = a + b + g;
    alpha = a / sum;
    beta = b / sum;
    gamma = g / sum;
}
