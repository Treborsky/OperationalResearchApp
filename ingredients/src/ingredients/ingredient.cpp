//
// Created by Robert Koziarski on 03.11.2021.
//

#include "ingredient.h"

#include <ostream>

#define DEF_EXP_DATE 7
#define DEF_ING_NAME "ingredient"

uint16_t Product::m_productsNumber = 0;   // private static member

Product::Product() : m_expiryDate(DEF_EXP_DATE), name(DEF_ING_NAME) {
    m_productsNumber++;
}

Product::Product(std::string &prod_name) : m_expiryDate(DEF_EXP_DATE), name(prod_name) {
    m_productsNumber++;
}

Product::Product(std::string &prod_name, uint8_t exp_date) : m_expiryDate(exp_date), name(prod_name) {
    m_productsNumber++;
}

Product::Product(std::string &&prod_name, uint8_t exp_date) : m_expiryDate(exp_date), name(std::move(prod_name)) {
    m_productsNumber++;
}

Product::~Product() {
    m_productsNumber--;
}

std::ostream &operator<<(std::ostream &out, const Ingredient &ingredient) {
    out << ingredient.product.name << " : " << ingredient.amount;
    return out;
}
