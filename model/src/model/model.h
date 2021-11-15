//
// Created by User on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include <app_data/app_data.h>

struct Solution {
    Solution(AppData& data, std::vector<bool>& selection);

    double costFunction(CostFunctionParams& params) const;
private:
    double calculateMshop();
    double calculateMloss();
    double calculateTtotal();

    AppData appData;
    std::vector<bool> selectedRecipes;
};

#endif //OPERATIONALRESEARCHAPP_MODEL_H
