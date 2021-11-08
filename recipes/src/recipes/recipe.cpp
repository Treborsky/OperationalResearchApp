//
// Created by User on 04.11.2021.
//

#include "recipe.h"

#include <ostream>

#define DEF_REC_NAME "Empty"
#define DEF_PREP_TIME 10

uint16_t Recipe::m_recipesNumber = 0;

Recipe::Recipe() : m_ingredientsForRecipe(std::vector<Ingredient>()), name(DEF_REC_NAME), prepTime(DEF_PREP_TIME) {
    m_recipesNumber++;
}

Recipe::Recipe(std::vector<Ingredient> &ingredients, uint16_t prepTime)
: m_ingredientsForRecipe(ingredients), name(DEF_REC_NAME), prepTime(prepTime) {
    m_recipesNumber++;
}

Recipe::Recipe(std::vector<Ingredient> &ingredients, std::string &name, uint16_t prepTime)
: m_ingredientsForRecipe(ingredients), name(name), prepTime(prepTime) {
    m_recipesNumber++;
}

Recipe::Recipe(std::vector<Ingredient> &ingredients, std::string &&name, uint16_t prepTime)
        : m_ingredientsForRecipe(ingredients), name(name), prepTime(prepTime) {
    m_recipesNumber++;
}

Recipe::~Recipe() {
    m_recipesNumber--;
}

const Ingredient& Recipe::operator[](std::size_t idx) const {
    return m_ingredientsForRecipe[idx];
}

std::ostream &operator<<(std::ostream &out, const Recipe& recipe) {
    out << "Recipe for: " << recipe.name << std::endl << '\t';
    for(const auto& ingredient : recipe.getRecipeList()) {
        out << ingredient << " | ";
    }
    out << std::endl << "\tPreparation time: " << recipe.prepTime;
    return out;
}
