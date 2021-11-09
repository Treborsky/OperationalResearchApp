//
// Created by User on 09.11.2021.
//

#include "utility.h"

#include <fstream>

namespace app {

    AppData& loadData(std::string& pathString, AppData& appData) {
        // load the file (using cpp11 constructors like a barbarian)
        std::ifstream dataFile(pathString);

        // read it line by line, interpreting the stuff inside
        std::string line;
        if(dataFile.is_open()) {
            while (dataFile.good()) {
                dataFile >> line;
                appData.parseLine(line);
            }
        }

        // save all of the stuff from it into appData
        // return appData
        return appData;
    }

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