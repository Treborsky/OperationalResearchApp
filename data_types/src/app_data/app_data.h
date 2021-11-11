//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_APP_DATA_H
#define OPERATIONALRESEARCHAPP_APP_DATA_H

#include <utility/utility.h>
#include <ingredients/ingredient.h>
#include <recipes/recipe.h>
#include <supplies/supply.h>

std::ostream& operator<<(std::ostream& os, const Ingredient&);
std::ostream& operator<<(std::ostream& os, const Recipe&);
std::ostream& operator<<(std::ostream& os, const Supply&);

struct AppData {
    AppData() {
        availableRecipies.reserve(10);
        storedIngredients.reserve(15);
        shopSupplies.reserve(10);
    }
    void loadData(std::string& filepath);

    std::vector<Recipe> availableRecipies;
    std::vector<Ingredient> storedIngredients;
    std::vector<Supply> shopSupplies;

    friend std::ostream& operator<<(std::ostream& os, const AppData&);
private:
    void parseLine(std::string& line);
};

std::ostream& operator<<(std::ostream& os, const AppData&);

#endif //OPERATIONALRESEARCHAPP_APP_DATA_H
