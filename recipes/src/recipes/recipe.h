//
// Created by Robert Koziarski on 04.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_RECIPE_H
#define OPERATIONALRESEARCHAPP_RECIPE_H

#include <cstdint>
#include <vector>
#include <ingredients/ingredient.h>

class Recipe {
public:
    Recipe();
    [[maybe_unused]] Recipe(std::vector<Ingredient>& ingredients);
    ~Recipe();
private:
    static uint16_t m_recipesNumber;
    std::vector<Ingredient> m_ingredientsForRecipe;
};

#endif //OPERATIONALRESEARCHAPP_RECIPE_H
