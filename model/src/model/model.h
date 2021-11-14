//
// Created by User on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include <app_data/app_data.h>

struct Solution {
    Solution(AppData& data, std::vector<bool>& selection);

    double costFunction(app::CostFunctionParams& params) const;
private:
    double calculateMshop() const;
    double calculateMloss() const;
    double calculateTtotal() const;

    AppData appData;
    std::vector<bool> selectedRecipes;
};

// TODO:

#endif //OPERATIONALRESEARCHAPP_MODEL_H
