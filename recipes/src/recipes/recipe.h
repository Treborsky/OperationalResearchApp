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
    explicit Recipe(std::vector<Ingredient> &ingredients, uint16_t prepTime);
    Recipe(std::vector<Ingredient> &ingredients, std::string &name, uint16_t prepTime);
    Recipe(std::vector<Ingredient> &ingredients, std::string &&name, uint16_t prepTime);
    ~Recipe();

    const std::vector<Ingredient> &getRecipeList() const { return m_ingredientsForRecipe; }

    const Ingredient& operator[](std::size_t idx) const;

    static uint16_t getRecipesNumber() { return m_recipesNumber; }

    std::string name;
    uint16_t prepTime;
private:
    static uint16_t m_recipesNumber;
    std::vector<Ingredient> m_ingredientsForRecipe;
};

std::ostream &operator<<(std::ostream &out, const Recipe& recipe);

#endif //OPERATIONALRESEARCHAPP_RECIPE_H