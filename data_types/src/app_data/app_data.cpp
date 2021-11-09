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
     * r - list of ingredients for the recipe, then prep time
     * i - list of ingredients that we currently store
     * s - list of available items in the store
     * */
    std::vector<std::string> tokenList = app::strSplit(line, ',');
    if (tokenList[0] == "r") { // parse the list of ingredients and put together a recipe
        if (tokenList.size() - 1 % 3 != 0) {
            return;
        }
        std::vector<Ingredient> ingredients();

        std::size_t i = 1;
        bool isWord;
        for(; i < tokenList.size() - 1; i += 1) {

            if (isWord) {

            }
        }
    } else if (tokenList[0] == "i") { // store the list of ingredients

    } else if (tokenList[0] == "s") { // update the available products

    } else {
        return;
    }
}

}