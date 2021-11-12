//
// Created by User on 09.11.2021.
//

#include "app_data.h"

void AppData::loadData(std::string &filepath) {
    std::ifstream dataFile(filepath);
    std::cout << "\nOpening file\n" << std::endl;
    // read it line by line, interpreting the stuff inside
    std::string line;
    if(dataFile.is_open()) {
        std::cout << "File opened successfully" << std::endl;
        while (dataFile.good()) {
            dataFile >> line;
            std::cout << "line to interpret:\t" << line << std::endl;
            parseLine(line);
        }
    }
    std::cout << "\nClosing file\n" << std::endl;
}

void AppData::parseLine(std::string& line) {
    /* a line consists of a type specifier:
     * r - recipes
     * i - ingredients
     * s - supplies
     * and then a list of the items of the type:
     * r - list of ingredients for the recipe, then prep time
     * i - list of ingredients that we currently store
     * s - list of available items in the store
     * */
    std::vector<std::string> tokenList = app::strSplit(line, ',');

    if (tokenList[0] == "r") { // parse the list of ingredients and put together a recipe
        std::vector<Ingredient> ingredients;
        int expDate;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 1; i += 2) { // starting from second token, ending before the last
            name = tokenList[i];
            std::cout << "INPUT NAME: " << tokenList[i] << "\t" << "WRITTEN NAME: " << name << "\n\t";
            expDate =  std::stoi(tokenList[i + 1]);
            std::cout << "INPUT DATE: " << tokenList[i + 1] << "\t" << "WRITTEN DATE: " << expDate << "\n\t";
            ingredients.emplace_back(Ingredient(expDate, name));
        }

        int prepTime;
        prepTime = std::stoi(tokenList[tokenList.size() - 1]);

        Recipe newRecipe(prepTime, ingredients);

        availableRecipies.emplace_back(newRecipe);

    } else if (tokenList[0] == "i") { // store the list of ingredients
        int expDate;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 2; i++) { // starting from second token, ending before the last
            expDate = std::stoi(tokenList[i + 2]);
            name = tokenList[i];
            storedIngredients.emplace_back(Ingredient(expDate, name));
            i += 2; // step size is 3, we skip over 2 things
        }
    } else if (tokenList[0] == "s") { // update the available products
        int expDate;
        std::string name;
        int price;

        for(std::size_t i = 1; i < tokenList.size() - 2; i++) { // starting from second token, ending before the last
            expDate = std::stoi(tokenList[i + 2]);
            price = std::stoi(tokenList[i + 1]);
            name = tokenList[i];
            shopSupplies.emplace_back(Supply(price, expDate, name));
            i += 2; // step size is 3, we skip over 2 things
        }
    } else {
        return;
    }
}

std::ostream& operator<<(std::ostream& os, const AppData& appData) {
    os << "AppData\n";
    os << "Recipe count: " << appData.availableRecipies.size() << "\n";
    os << "Ingredients count: " << appData.storedIngredients.size() << "\n";
    os << "Supply count: " << appData.shopSupplies.size() << "\n";

    for(const auto& recipe : appData.availableRecipies) {
        os << recipe << "\n\t";
    }
    for(const auto& ingredient : appData.storedIngredients) {
        os << ingredient << "\n\t";
    }
    for(const auto& supply : appData.shopSupplies) {
        os << supply << "\n\t";
    }
    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
    os << "Ingredient:\n\t-\t" << ingredient.name << "\n\t-\t" << ingredient.expirationDate << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Recipe& recipe) {
    os << "Recipe:\n\t-\t" << "Preparation time: " << recipe.preparationTime << "\n\t";
    os << "Ingredient list:\n\t";
    for(auto& ingredient : recipe.ingredientList) {
        os << ingredient << "\n\t";
    }
    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Supply& supply) {
    os << "Supply\n\t-\t" << supply.name << "\n\t-\t" << supply.expirationDate << "\n\t-\t" << supply.price << std::endl;
    return os;
}