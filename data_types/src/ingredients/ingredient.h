//
// Created by User on 03.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_INGREDIENT_H
#define OPERATIONALRESEARCHAPP_INGREDIENT_H

#include <utility/utility.h>

struct Ingredient {
    explicit Ingredient(std::size_t expDate=10, std::string_view newName="unnamed")
        : expirationDate(expDate), name(newName) {}
    std::size_t expirationDate;
    std::string name;
};

#endif //OPERATIONALRESEARCHAPP_INGREDIENT_H
