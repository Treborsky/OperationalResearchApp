//
// Created by Robert Koziarski on 03.11.2021.
//

#include "ingredient.h"

#define DEF_EXP_DATE 7
#define DEF_ING_NAME "ingredient"

uint16_t Ingredient::m_ingredientsNumber = 0;   // private static member

Ingredient::Ingredient() : m_expiryDate(DEF_EXP_DATE) {
    name = DEF_ING_NAME;
    m_ingredientsNumber++;
}

Ingredient::~Ingredient() {
    m_ingredientsNumber--;
}