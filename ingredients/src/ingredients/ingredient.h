//
// Created by User on 03.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_INGREDIENT_H
#define OPERATIONALRESEARCHAPP_INGREDIENT_H

#include <cstdint>
#include <string>

class Ingredient {
public:
    Ingredient();
    ~Ingredient();
    std::string name;
private:
    static uint16_t m_ingredientsNumber;
    uint8_t m_expiryDate;
}

#endif //OPERATIONALRESEARCHAPP_INGREDIENT_H
