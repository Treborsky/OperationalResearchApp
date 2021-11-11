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
    std::stringstream s;

    std::cout << "Parsing tokens: ";
    for(const auto& token : tokenList) {
        std::cout << "'" << token << "'" << " | ";
    }
    std::cout << std::endl;
    std::string firstToken;
    s << tokenList[0];
    s >> firstToken;
    if (firstToken == "r") { // parse the list of ingredients and put together a recipe

        std::vector<Ingredient> ingredients;
        std::size_t expDate;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 1; i+=2) { // starting from second token, ending before the last
            s << tokenList[i + 1];
            s >> expDate;
            s << tokenList[i];
            s >> name;
            std::cout << "expDate: " << expDate << " | name: " << name << std::endl;
            ingredients.emplace_back(Ingredient(expDate, name));
        }
        std::size_t prepTime;
        s << tokenList[tokenList.size() - 1];
        s >> prepTime;

        Recipe newRecipe(prepTime, ingredients);

        availableRecipies.emplace_back(newRecipe);

    } else if (firstToken == "i") { // store the list of ingredients
        if((tokenList.size() - 1) % 3 != 0) {
            return;
        }
        std::size_t expDate;
        std::string name;

        for(std::size_t i = 1; i < tokenList.size() - 2; i++) { // starting from second token, ending before the last
            s << tokenList[i + 2];
            s >> expDate;
            s << tokenList[i];
            s >> name;
            storedIngredients.emplace_back(Ingredient(expDate, name));
            i += 2; // step size is 3, we skip over 2 things
        }

    } else if (firstToken == "s") { // update the available products
        if ((tokenList.size() - 1) % 3 != 0) {
            return;
        }
        std::size_t expDate;
        std::string name;
        std::size_t price;

        for(std::size_t i = 1; i < tokenList.size() - 2; i++) { // starting from second token, ending before the last
            s << tokenList[i + 2];
            s >> expDate;
            s << tokenList[i + 1];
            s >> price;
            s << tokenList[i];
            s >> name;
            shopSupplies.emplace_back(Supply(price, expDate, name));
            i += 2; // step size is 3, we skip over 2 things
        }

    } else {
        return;
    }
}

std::ostream& operator<<(std::ostream& os, const AppData& appData) {
    os << "AppData\n\t";
    os << "Recipe count: " << appData.availableRecipies.size() << "\n\t";
    os << "Ingredients count: " << appData.storedIngredients.size() << "\n\t";
    os << "Supply count: " << appData.shopSupplies.size() << "\n\t";

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
    os << "Ingredient:\n\t" << ingredient.name << "\n\t" << ingredient.expirationDate << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Recipe& recipe) {
    os << "Recipe:\n\t" << "preparation time: " << recipe.preparationTime << "\n\t";
    for(auto& ingredient : recipe.ingredientList) {
        os << ingredient << "\n\t";
    }
    os << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Supply& supply) {
    os << "Supply\n\t" << supply.name << "\n\t" << supply.expirationDate << "\n\t" << supply.price << std::endl;
    return os;
}