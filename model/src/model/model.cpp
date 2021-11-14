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

double Solution::costFunction(app::CostFunctionParams& params) const {
    const double Mshop = calculateMshop();
    const double Mloss = calculateMloss();
    const double Ttotal = calculateTtotal();

    return params.alpha * Mshop + params.beta * Mloss + params.gamma * Ttotal;
}

double Solution::calculateMshop() const {

    return 0.0;
}

double Solution::calculateMloss() const {
    return 0.0;
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