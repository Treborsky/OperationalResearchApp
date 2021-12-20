//
// Created by User on 14.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_MODEL_H
#define OPERATIONALRESEARCHAPP_MODEL_H

#include "app_data.h"

struct Solution {
    Solution(AppData& data, std::vector<bool>& selection, int today, int money);
    ~Solution() = default;
    double costFunction(CostFunctionParams& params);
private:
    double sumPurchases();
    double sumLosses();
    double sumTime();

    AppData app_data;
    std::vector<bool> selected_recipes;
    int today;
    int money;
};

#endif //OPERATIONALRESEARCHAPP_MODEL_H
