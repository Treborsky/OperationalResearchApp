//
// Created by User on 14.11.2021.
//

#include "model.h"

Solution::Solution(AppData& data, std::vector<bool>& selection, int money, int today)
    : app_data(data), money(money), today(today) {
    if (selection.size() == data.recipes.size()) {
        selected_recipes = std::move(selection);
    } else {
        std::cout << "Invalid selection of recipies provided, empty vector will be initialized" << std::endl;
        selected_recipes = std::vector<bool>();
        selected_recipes.reserve(data.recipes.size());
    }
}

double Solution::costFunction(CostFunctionParams& params) {
    double Mloss = sumLosses();
    double Mshop = sumPurchases();
    double Ttotal = sumTime();

    return params.alpha * Mshop + params.beta * Mloss + params.gamma * Ttotal;
}

double Solution::sumPurchases() {
    double Mshop = 0.0;
    for(std::size_t j = 0; j < selected_recipes.size(); ++j) {
        // determine if we have all ingredients for the recipe
        // if we don't have enough amount of an ingredient, then we buy one (we add the cost and increase
        // the ingredient amount)
        // we also need to subtract the amount used in the recipe
        if (selected_recipes[j]) { // we select recipes[j]
            Recipe currentRecipe = app_data.recipes[j];
            for(const auto& currentRecipeIngredient : currentRecipe.list) {
                // search through the ingredient list and determine if we have enough of the ingredient
                std::size_t idxIfWeHaveIt = -1;
                bool isEnough = false;
                for (std::size_t k = 0; k < app_data.ingredients.size(); ++k) {
                    if (app_data.ingredients[k].name == currentRecipeIngredient.name) { // do we have it on the list
                        idxIfWeHaveIt = k;
                        if (app_data.ingredients[k].amount >= currentRecipeIngredient.amount) { // do we have enough of the thing
                            isEnough = true; // we have enough of the thing do make the recipe
                            break;
                        }
                        break;
                    }
                }
                if (!isEnough) { // then we have to buy it
                    for (std::size_t k = 0; k < app_data.supplies.size(); ++k) { // we want to find a supply with the same name
                        if (app_data.supplies[k].name == currentRecipeIngredient.name) { // if we found it, we buy it
                            Mshop += app_data.supplies[k].price; // we buy it
                            // TODO: include the money variable from the mathematical model, right now we have basically infinite resources
                            if (idxIfWeHaveIt != -1) { // we have some, but not enough
                                app_data.ingredients[idxIfWeHaveIt].amount += app_data.supplies[k].amount;
                            } else { // if we didn't have it in the first place
                                int expDate = app_data.ingredients[k].expiry_date;
                                int amount = app_data.ingredients[k].amount;
                                std::string name = app_data.ingredients[k].name;
                                app_data.ingredients.emplace_back(Ingredient(expDate, amount, name));
                            }
                            break;
                        }
                    }
                }
                app_data.ingredients[idxIfWeHaveIt].amount -= currentRecipeIngredient.amount; // we use up some of it
            }
        }
    }
    return Mshop;
}

double Solution::sumLosses() {
    double Mloss = 0.0;
    for(std::size_t j = 0; j < selected_recipes.size(); ++j) {
        if (!selected_recipes[j]) { // the ith recipe is taken into the solution
            Recipe currentRecipe = app_data.recipes[j];
            for(auto & i : currentRecipe.list) {
                if(i.expiry_date <= today) {
                    // TODO: redefine ingredient so that is has a price
                    for(const auto& supply : app_data.supplies) {
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

double Solution::sumTime() {
    double Ttotal = 0.0;
    for(std::size_t i = 0; i < app_data.recipes.size(); ++i) {
        if (selected_recipes[i]) {
            Ttotal += app_data.recipes[i].preparation_time;
        }
    }
    return Ttotal;
}