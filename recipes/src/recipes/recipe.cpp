//
// Created by User on 04.11.2021.
//

#include "recipe.h"

uint16_t Recipe::m_recipesNumber = 0;

Recipe::Recipe() {
    m_recipesNumber++;
}

[[maybe_unused]] Recipe::Recipe(std::vector<Ingredient> &ingredients) : m_ingredientsForRecipe(ingredients) {
    m_recipesNumber++;
}

Recipe::~Recipe() {
    m_recipesNumber--;
}