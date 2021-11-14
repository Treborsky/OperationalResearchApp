//
// Created by User on 14.11.2021.
//

#include "model.h"

Solution::Solution(AppData& data, std::vector<bool>& selection) : appData(std::move(data)) {
    if (selection.size() == data.availableRecipies.size()) {
        selectedRecipes = std::move(selection);
    } else {
        std::cout << "Invalid selection of recipies provided, empty vector will be initialized" << std::endl;
        selectedRecipes = std::vector<bool>();
        selectedRecipes.reserve(data.availableRecipies.size());
    }
}

double Solution::costFunction(CostFunctionParams& params) const {
    const double Mshop = calculateMshop();
    const double Mloss = calculateMloss();
    const double Ttotal = calculateTtotal();

    return params.alpha * Mshop + params.beta * Mloss + params.gamma * Ttotal;
}

double Solution::calculateMshop() const {
    double Mshop = 0.0;
    for(std::size_t j = 0; j < selectedRecipes.size(); ++j) {
        // determine if we have all ingredients for the recipe
        // if we don't have enough amount of an ingredient, then we buy one (we add the cost and increase
        // the ingredient amount)
        if (selectedRecipes[j]) { // we select availableRecipies[i]
            for(std::size_t i = 0; i < appData.availableRecipies[i].ingredientList.size(); ++i) {
                // search through the ingredient list and determine if we have enough of the ingredient
                Ingredient currentRecipeIngredient = appData.availableRecipies[j].ingredientList[i];
                std::size_t idxIfWeHaveIt = -1;
                bool isEnough = false;
                for(std::size_t k = 0; k < appData.storedIngredients.size(); ++k) {
                    if (appData.storedIngredients[k].name == currentRecipeIngredient.name) { // do we have it on the list
                        idxIfWeHaveIt = k;
                        if (appData.storedIngredients[k].amount >= currentRecipeIngredient.amount) { // do we have enough of the thing
                            isEnough = true; // we have enough of the thing do make the recipe
                            break;
                        }
                        break;
                    }
                }
                if (!isEnough) { // then we have to buy it
                    for(std::size_t k = 0; k < appData.shopSupplies.size(); ++k) { // we want to find a supply with the same name
                        if (appData.shopSupplies[k].name == currentRecipeIngredient.name) { // if we found it, we buy it
                            Mshop += (double)appData.shopSupplies[k].price; // we buy it
                            // TODO: include the Money variable from the mathematical model, right now we have
                            // basically infinite resources
                            if (idxIfWeHaveIt != -1) {
                                appData.storedIngredients[idxIfWeHaveIt].amount += appData.shopSupplies[k].amount; // TODO: fix this stuff
                                // because of C++20, we have to rewrite the entire vector of ingredients to update one element -> wtf
                                int expDate = appData.storedIngredients[idxIfWeHaveIt].expirationDate;
                                int amount = appData.storedIngredients[idxIfWeHaveIt].amount;
                                std::string name = appData.storedIngredients[idxIfWeHaveIt].name;

                                Ingredient updatedIngredient(expDate, amount + appData.shopSupplies[k].amount, name);

                                std::vector<Ingredient> newStoredIngredients;
                                newStoredIngredients.reserve(appData.storedIngredients.size());

                                for(std::size_t l = 0; l < appData.storedIngredients.size(); ++l) {
                                    if (l != idxIfWeHaveIt) {
                                        newStoredIngredients.push_back(appData.storedIngredients[l]);
                                    } else {
                                        newStoredIngredients.push_back(updatedIngredient);
                                    }
                                } // we bought it goddamit, we also updated the vector

                            } else { // if we didn't have it in the first place
                                int expDate = appData.storedIngredients[k].expirationDate;
                                int amount = appData.storedIngredients[k].amount;
                                std::string name = appData.storedIngredients[k].name;
                                appData.storedIngredients.emplace_back(Ingredient(expDate, amount, name));
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0.0;
}

double Solution::calculateMloss() const {
    double Mloss = 0.0;

    return Mloss;
}

double Solution::calculateTtotal() const {
    double Ttotal = 0.0;
    for(std::size_t i = 0; i < appData.availableRecipies.size(); ++i) {
        if (selectedRecipes[i]) {
            Ttotal += appData.availableRecipies[i].preparationTime;
        }
    }
    return Ttotal;
}