//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_APP_DATA_H
#define OPERATIONALRESEARCHAPP_APP_DATA_H

#include <utility/utility.h>

struct AppData {
    AppData();

    void parseLine(std::string& line);

    std::vector<Recipe> availableRecipies;
    std::vector<Ingredient> storedIngredients;
    std::vector<Supply> shopSupplies;
};

#endif //OPERATIONALRESEARCHAPP_APP_DATA_H
