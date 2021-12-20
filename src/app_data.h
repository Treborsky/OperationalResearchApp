//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_APP_DATA_H
#define OPERATIONALRESEARCHAPP_APP_DATA_H

#include "utility.h"

struct Ingredient {
    explicit Ingredient(int expDate=10, int am=100, std::string newName="unnamed")
            : expiryDate(expDate), amount(am), name(std::move(newName)) {}
    ~Ingredient() = default;
    int expiryDate;
    int amount;
    std::string name;
};

struct Recipe {
    explicit Recipe(int prepTime, std::vector<Ingredient> &ingredients)
            : list(ingredients), preparationTime(prepTime) {}
    ~Recipe() = default;
    int preparationTime;
    std::vector<Ingredient> list;
};

struct Supply : public Ingredient {
    explicit Supply(int supplyPrice, int amount=100, int expDate=10, std::string newName="unnamed")
            : price(supplyPrice), Ingredient(expDate, amount, std::move(newName)) {}
    ~Supply() = default;
    int price;
};

std::ostream& operator<<(std::ostream& os, const Ingredient&);
std::ostream& operator<<(std::ostream& os, const Recipe&);
std::ostream& operator<<(std::ostream& os, const Supply&);

struct AppData {
    ~AppData() = default;
    void loadData(std::string& filepath);

    void updateIngredient(Ingredient& ingredient, std::size_t idx) { ingredients[idx] = ingredient; }
    void updateIngredient(Ingredient&& ingredient, std::size_t idx) { ingredients[idx] = ingredient; }
    void addIngredient(Ingredient& ingredient) { ingredients.emplace_back(ingredient); }
    void addIngredient(Ingredient&& ingredient) { ingredients.emplace_back(ingredient); }

    std::vector<Recipe> recipes;
    std::vector<Ingredient> ingredients;
    std::vector<Supply> supplies;

    friend std::ostream& operator<<(std::ostream& os, const AppData&);
private:
    void parseLine(std::string& line);
};

std::ostream& operator<<(std::ostream& os, const AppData&);



#endif //OPERATIONALRESEARCHAPP_APP_DATA_H
