//
// Created by User on 04.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_RECIPE_H
#define OPERATIONALRESEARCHAPP_RECIPE_H

#include <ingredients/ingredient.h>

struct Recipe {
    explicit Recipe(int prepTime, std::vector<Ingredient> &ingredients)
        : ingredientList(ingredients), preparationTime(prepTime) {}
    int preparationTime;
    std::vector<Ingredient> ingredientList;
};


#endif //OPERATIONALRESEARCHAPP_RECIPE_H