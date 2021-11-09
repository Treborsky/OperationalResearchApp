//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_SUPPLY_H
#define OPERATIONALRESEARCHAPP_SUPPLY_H

#include <ingredients/ingredient.h>

struct Supply : Ingredient {
    explicit Supply(app::ushort supplyPrice, app::ushort expDate=10, app::string_v newName="unnamed")
        : price(supplyPrice), Ingredient(expDate, newName) {}
    app::ushort price;
};

#endif //OPERATIONALRESEARCHAPP_SUPPLY_H
