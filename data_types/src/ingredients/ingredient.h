//
// Created by User on 03.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_INGREDIENT_H
#define OPERATIONALRESEARCHAPP_INGREDIENT_H

#include <utility/utility.h>

struct Ingredient {
    explicit Ingredient(int expDate=10, int am=100, std::string newName="unnamed")
        : expirationDate(expDate), amount(am), name(std::move(newName)) {}

    int expirationDate;
    int amount;
    std::string name;
};


#endif //OPERATIONALRESEARCHAPP_INGREDIENT_H
