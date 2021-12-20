//
// Created by User on 09.11.2021.
//

#include "app_data.h"

void AppData::loadData(std::string &filepath) {
    std::ifstream data_file(filepath);
    std::cout << "Opening file" << std::endl;
    // read it line by line, interpreting the stuff inside
    std::string line;
    if(data_file.is_open()) {
        std::cout << "File opened successfully" << std::endl;
        while (data_file.good()) {
            data_file >> line;
            parseLine(line);
        }
    }
    std::cout << "\nClosing file\n" << std::endl;
}

void AppData::parseLine(std::string& line) {
    /*  Parses the given line from a .csv file
        a line consists of a type specifier:
            r - recipes
            i - ingredients
            s - supplies
        and then a list of the items of the type:
            r - list of ingredients for the recipe, then prep time
            i - list of ingredients that we currently store
            s - list of available items in the store
 */

    std::vector<std::string> token_list = strSplit(line, ',');

    if (token_list[0] == "r") { // parse the list of ingredients and put together a recipe
        std::vector<Ingredient> ingredients;
        int amount;
        std::string name;

        for(std::size_t i = 1; i < token_list.size() - 1; i += 2) { // starting from second token, ending before the last
            name = token_list[i];
            amount =  std::stoi(token_list[i + 1]);
            ingredients.emplace_back(Ingredient(10, amount, name));
        }

        int prep_time;
        prep_time = std::stoi(token_list[token_list.size() - 1]);

        Recipe new_recipe(prep_time, ingredients);

        recipes.emplace_back(new_recipe);

    } else if (token_list[0] == "i") { // store the list of ingredients
        int exp_date;
        int amount;
        std::string name;

        for(std::size_t i = 1; i < token_list.size() - 2; i += 3) { // starting from second token
            name = token_list[i];
            amount = std::stoi(token_list[i + 1]);
            exp_date = std::stoi(token_list[i + 2]);
            ingredients.emplace_back(Ingredient(exp_date, amount, name));
        }
    } else if (token_list[0] == "s") { // update the available products
        int exp_date;
        int amount;
        std::string name;
        int price;

        for(std::size_t i = 1; i < token_list.size() - 3; i += 4) { // starting from second token
            name = token_list[i];
            amount = std::stoi(token_list[i + 1]);
            price = std::stoi(token_list[i + 2]);
            exp_date = std::stoi(token_list[i + 3]);
            supplies.emplace_back(Supply(price, amount, exp_date, name));
        }
    } else {
        return;
    }
}

// STREAM OPERATORS
std::ostream& operator<<(std::ostream& os, const AppData& appData) {
    os << "AppData\n";
    os << "Recipe count: " << appData.recipes.size() << "\n";
    os << "Ingredients count: " << appData.ingredients.size() << "\n";
    os << "Supply count: " << appData.supplies.size() << "\n\t";

    for(const auto& recipe : appData.recipes) {
        os << recipe << "\n\t";
    }
    for(const auto& ingredient : appData.ingredients) {
        os << ingredient << "\n\t";
    } os << "\n\t";
    for(const auto& supply : appData.supplies) {
        os << supply << "\n\t";
    } os << "\n\t";

    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
    os << "Ingredient:\n\t-\t" << ingredient.name << "\n\t-\t" << ingredient.expiry_date << "\n\t-\t" << ingredient.amount << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Recipe& recipe) {
    os << "Recipe:\n\t-\t" << "Preparation time: " << recipe.preparation_time << "\n\t";
    os << "Ingredient list:\n\t";
    for(auto& ingredient : recipe.list) {
        os << ingredient << "\n\t";
    }
    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Supply& supply) {
    os << "Supply:\n\t-\t" << supply.name << "\n\t-\t" << supply.expiry_date << "\n\t-\t" << supply.price << std::endl;
    return os;
}