//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_APP_DATA_H
#define OPERATIONALRESEARCHAPP_APP_DATA_H

#include "utility.h"

struct Ingredient {
    explicit Ingredient(int exp_date=10, int am=100, std::string new_name="unnamed")
            : expiry_date(exp_date), amount(am), name(std::move(new_name)) {}
    ~Ingredient() = default;
    int expiry_date;
    int amount;
    std::string name;
};

struct Recipe {
    explicit Recipe(int prep_time, std::vector<Ingredient> &ingredients)
            : list(ingredients), preparation_time(prep_time) {}
    ~Recipe() = default;
    int preparation_time;
    std::vector<Ingredient> list;
};

struct Supply : public Ingredient {
    explicit Supply(int supply_price, int amount=100, int exp_date=10, std::string new_name="unnamed")
            : price(supply_price), Ingredient(exp_date, amount, std::move(new_name)) {}
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
