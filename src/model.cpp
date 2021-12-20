//
// Created by User on 14.11.2021.
//

#include "model.h"

Solution::Solution(AppData& data, std::vector<bool>& selection, int money, int today)
    : appData(data), Money(money), Today(today) {
    if (selection.size() == data.recipes.size()) {
        selectedRecipes = std::move(selection);
    } else {
        std::cout << "Invalid selection of recipies provided, empty vector will be initialized" << std::endl;
        selectedRecipes = std::vector<bool>();
        selectedRecipes.reserve(data.recipes.size());
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
        if (selectedRecipes[j]) { // we select recipes[j]
            Recipe currentRecipe = appData.recipes[j];
            for(const auto& currentRecipeIngredient : currentRecipe.list) {
                // search through the ingredient list and determine if we have enough of the ingredient
                std::size_t idxIfWeHaveIt = -1;
                bool isEnough = false;
                for (std::size_t k = 0; k < appData.ingredients.size(); ++k) {
                    if (appData.ingredients[k].name == currentRecipeIngredient.name) { // do we have it on the list
                        idxIfWeHaveIt = k;
                        if (appData.ingredients[k].amount >= currentRecipeIngredient.amount) { // do we have enough of the thing
                            isEnough = true; // we have enough of the thing do make the recipe
                            break;
                        }
                        break;
                    }
                }
                if (!isEnough) { // then we have to buy it
                    for (std::size_t k = 0; k < appData.supplies.size(); ++k) { // we want to find a supply with the same name
                        if (appData.supplies[k].name == currentRecipeIngredient.name) { // if we found it, we buy it
                            Mshop += appData.supplies[k].price; // we buy it
                            // TODO: include the Money variable from the mathematical model, right now we have basically infinite resources
                            if (idxIfWeHaveIt != -1) { // we have some, but not enough
                                appData.ingredients[idxIfWeHaveIt].amount += appData.supplies[k].amount;
                            } else { // if we didn't have it in the first place
                                int expDate = appData.ingredients[k].expiryDate;
                                int amount = appData.ingredients[k].amount;
                                std::string name = appData.ingredients[k].name;
                                appData.ingredients.emplace_back(Ingredient(expDate, amount, name));
                            }
                            break;
                        }
                    }
                }
                appData.ingredients[idxIfWeHaveIt].amount -= currentRecipeIngredient.amount; // we use up some of it
            }
        }
    }
    return Mshop;
}

double Solution::calculateMloss() {
    double Mloss = 0.0;
    for(std::size_t j = 0; j < selectedRecipes.size(); ++j) {
        if (!selectedRecipes[j]) { // the ith recipe is taken into the solution
            Recipe currentRecipe = appData.recipes[j];
            for(auto & i : currentRecipe.list) {
                if(i.expiryDate <= Today) {
                    // TODO: redefine ingredient so that is has a price
                    for(const auto& supply : appData.supplies) {
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
    for(std::size_t i = 0; i < appData.recipes.size(); ++i) {
        if (selectedRecipes[i]) {
            Ttotal += appData.recipes[i].preparationTime;
        }
    }
    return Ttotal;
}