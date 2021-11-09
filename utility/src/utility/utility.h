//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_UTILITY_H
#define OPERATIONALRESEARCHAPP_UTILITY_H

#include <cstdint>
#include <vector>
#include <string>
#include <string_view>
#include <set>

struct Supply;
struct Recipe;
struct Ingredient;
struct AppData;

namespace app {
    AppData& loadData(std::string& pathString, AppData& appData);
    std::vector<std::string> strSplit(std::string str, char delim);
}

#endif //OPERATIONALRESEARCHAPP_UTILITY_H
