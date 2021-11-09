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

class Ingredient;

namespace app {
    typedef uint16_t ushort;
    typedef std::vector<uint16_t> vector_ushort;
    typedef std::string string;
    typedef std::string_view string_v;
    typedef std::vector<Ingredient> vector_ingredient;
}

#endif //OPERATIONALRESEARCHAPP_UTILITY_H
