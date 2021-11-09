//
// Created by User on 09.11.2021.
//

#include "app_data.h"

void AppData::parseLine(std::string& line) {
    /* a line consists of a type specifier:
     * r - recipes
     * i - ingredients
     * s - supplies
     * and then a list of the items of the type:
     * r - list of ingredients for the recipe
     * i - list of ingredients that we currently store
     * s - list of available items in the store
     * */
    std::vector<std::string> tokenList = app::strSplit(line, ',');
    if (tokenList[0] == "r") { // parse the list of ingredients and put together a recipe
        std::size_t i = 0;
    } else if (tokenList[0] == "i") { // store the list of ingredients

    } else if (tokenList[0] == "s") { // update the available products

    } else {
        return;
    }
}

}