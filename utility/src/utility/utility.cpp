//
// Created by User on 09.11.2021.
//

#include "utility.h"

namespace app {
    std::vector<std::string> strSplit(std::string str, char delim) {
        std::vector<std::string> tokens;
        tokens.reserve(30);     // completely arbitrary
        std::size_t pos = 0;
        std::string token;
        while((pos = str.find(delim)) != std::string::npos) {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + 1);
        }
        return tokens;
    }

}