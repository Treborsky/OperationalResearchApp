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

namespace app {
    std::vector<std::string> strSplit(std::string str, char delim);
    struct CostFunctionParams {
        explicit CostFunctionParams(double a=1.0, double b=1.0, double g=0.0) : alpha(a), beta(b), gamma(g) {}
        double alpha;
        double beta;
        double gamma;
    };
}

#endif //OPERATIONALRESEARCHAPP_UTILITY_H
