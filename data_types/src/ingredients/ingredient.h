//
// Created by User on 03.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_INGREDIENT_H
#define OPERATIONALRESEARCHAPP_INGREDIENT_H

#include <utility/utility.h>

struct Ingredient {
    explicit Ingredient(app::ushort expDate=10, app::string_v newName="unnamed")
        : expirationDate(expDate), name(newName) {}
    app::ushort expirationDate;
    app::string name;
};

#endif //OPERATIONALRESEARCHAPP_INGREDIENT_H
