//
// Created by User on 04.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_RECIPE_H
#define OPERATIONALRESEARCHAPP_RECIPE_H

#include <ingredients/ingredient.h>

struct Recipe {
    explicit Recipe(app::ushort prepTime, app::vector_ingredient &ingredients)
        : ingredientList(ingredients), preparationTime(prepTime) {}
    app::ushort preparationTime;
    app::vector_ingredient ingredientList;
};

#endif //OPERATIONALRESEARCHAPP_RECIPE_H