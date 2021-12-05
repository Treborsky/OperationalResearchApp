//
// Created by User on 14.11.2021.
//

#include "model.h"

Solution::Solution(AppData& data, std::vector<bool>& selection, int money, int today)
    : appData(data), Money(money), Today(today) {
    if (selection.size() == data.availableRecipies.size()) {
        selectedRecipes = std::move(selection);
    } else {
        std::cout << "Invalid selection of recipies provided, empty vector will be initialized" << std::endl;
        selectedRecipes = std::vector<bool>();
        selectedRecipes.reserve(data.availableRecipies.size());
    }
}

double Solution::costFunction(CostFunctionParams& params) {
    double Mloss = calculateMloss();
    double Mshop = calculateMshop();
    double Ttotal = calculateTtotal();

    return params.alpha * Mshop + params.beta * Mloss + params.gamma * Ttotal;
}

double Solution::calculateMshop() {
    double Mshop = 0.0;
    for(std::size_t j = 0; j < selectedRecipes.size(); ++j) {
        // determine if we have all ingredients for the recipe
        // if we don't have enough amount of an ingredient, then we buy one (we add the cost and increase
        // the ingredient amount)
        // we also need to subtract the amount used in the recipe
        if (selectedRecipes[j]) { // we select availableRecipies[j]
            Recipe currentRecipe = appData.availableRecipies[j];
            for(const auto& currentRecipeIngredient : currentRecipe.ingredientList) {
                // search through the ingredient list and determine if we have enough of the ingredient
                std::size_t idxIfWeHaveIt = -1;
                bool isEnough = false;
                for (std::size_t k = 0; k < appData.storedIngredients.size(); ++k) {
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
                    for (std::size_t k = 0; k < appData.shopSupplies.size(); ++k) { // we want to find a supply with the same name
                        if (appData.shopSupplies[k].name == currentRecipeIngredient.name) { // if we found it, we buy it
                            Mshop += appData.shopSupplies[k].price; // we buy it
                            // TODO: include the Money variable from the mathematical model, right now we have basically infinite resources
                            if (idxIfWeHaveIt != -1) { // we have some, but not enough
                                appData.storedIngredients[idxIfWeHaveIt].amount += appData.shopSupplies[k].amount;
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
                appData.storedIngredients[idxIfWeHaveIt].amount -= currentRecipeIngredient.amount; // we use up some of it
            }
        }
    }
    return Mshop;
}

double Solution::calculateMloss() {
    double Mloss = 0.0;
    for(std::size_t j = 0; j < selectedRecipes.size(); ++j) {
        if (!selectedRecipes[j]) { // the ith recipe is taken into the solution
            Recipe currentRecipe = appData.availableRecipies[j];
            for(auto & i : currentRecipe.ingredientList) {
                if(i.expirationDate <= Today) {
                    // TODO: redefine ingredient so that is has a price
                    for(const auto& supply : appData.shopSupplies) {
                        if(supply.name == i.name) {
                            Mloss += supply.price;
                            break;
                        }
                    }
                }
            }
        }
    }
    return Mloss;
}

double Solution::calculateTtotal() {
    double Ttotal = 0.0;
    for(std::size_t i = 0; i < appData.availableRecipies.size(); ++i) {
        if (selectedRecipes[i]) {
            Ttotal += appData.availableRecipies[i].preparationTime;
        }
    }
    return Ttotal;
}