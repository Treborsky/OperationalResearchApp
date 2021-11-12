//
// Created by User on 09.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_SUPPLY_H
#define OPERATIONALRESEARCHAPP_SUPPLY_H

#include <ingredients/ingredient.h>

struct Supply : public Ingredient {
    explicit Supply(int supplyPrice, int expDate=10, std::string newName="unnamed")
        : price(supplyPrice), Ingredient(expDate, std::move(newName)) {}
    int price;
};


#endif //OPERATIONALRESEARCHAPP_SUPPLY_H
