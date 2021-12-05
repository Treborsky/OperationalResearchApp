//
// Created by User on 09.11.2021.
//

#include "app_data.h"

void AppData::loadData(std::string &filepath) {
    std::ifstream dataFile(filepath);
    std::cout << "Opening file" << std::endl;
    // read it line by line, interpreting the stuff inside
    std::string line;
    if(dataFile.is_open()) {
        std::cout << "File opened successfully" << std::endl;
        while (dataFile.good()) {
            dataFile >> line;
            parseLine(line);
        }
    }
    std::cout << "\nClosing file\n" << std::endl;
}

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
void AppData::parseLine(std::string& line) {
    std::vector<std::string> tokenList = strSplit(line, ',');

    if (tokenList[0] == "r") { // parse the list of ingredients and put together a recipe
        std::vector<Ingredient> ingredients;
        int amount;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 1; i += 2) { // starting from second token, ending before the last
            name = tokenList[i];
            amount =  std::stoi(tokenList[i + 1]);
            ingredients.emplace_back(Ingredient(10, amount, name));
        }

        int prepTime;
        prepTime = std::stoi(tokenList[tokenList.size() - 1]);

        Recipe newRecipe(prepTime, ingredients);

        availableRecipies.emplace_back(newRecipe);

    } else if (tokenList[0] == "i") { // store the list of ingredients
        int expDate;
        int amount;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 2; i += 3) { // starting from second token
            name = tokenList[i];
            amount = std::stoi(tokenList[i + 1]);
            expDate = std::stoi(tokenList[i + 2]);
            storedIngredients.emplace_back(Ingredient(expDate, amount, name));
        }
    } else if (tokenList[0] == "s") { // update the available products
        int expDate;
        int amount;
        std::string name;
        int price;

        for(std::size_t i = 1; i < tokenList.size() - 3; i += 4) { // starting from second token
            name = tokenList[i];
            amount = std::stoi(tokenList[i + 1]);
            price = std::stoi(tokenList[i + 2]);
            expDate = std::stoi(tokenList[i + 3]);
            shopSupplies.emplace_back(Supply(price, amount, expDate, name));
        }
    } else {
        return;
    }
}

std::ostream& operator<<(std::ostream& os, const AppData& appData) {
    os << "AppData\n";
    os << "Recipe count: " << appData.availableRecipies.size() << "\n";
    os << "Ingredients count: " << appData.storedIngredients.size() << "\n";
    os << "Supply count: " << appData.shopSupplies.size() << "\n\t";

    for(const auto& recipe : appData.availableRecipies) {
        os << recipe << "\n\t";
    }
    for(const auto& ingredient : appData.storedIngredients) {
        os << ingredient << "\n\t";
    } os << "\n\t";
    for(const auto& supply : appData.shopSupplies) {
        os << supply << "\n\t";
    } os << "\n\t";

    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
    os << "Ingredient:\n\t-\t" << ingredient.name << "\n\t-\t" << ingredient.expirationDate << "\n\t-\t" << ingredient.amount << std::endl;
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
    os << "Supply:\n\t-\t" << supply.name << "\n\t-\t" << supply.expirationDate << "\n\t-\t" << supply.price << std::endl;
    return os;
}