//
// Created by User on 03.11.2021.
//

#ifndef OPERATIONALRESEARCHAPP_INGREDIENT_H
#define OPERATIONALRESEARCHAPP_INGREDIENT_H

#include <cstdint>
#include <string>

typedef double Amount;

class Product {
public:
    Product();
    explicit Product(std::string& name);
    Product(std::string& name, uint8_t exp_date);
    Product(std::string&& name, uint8_t exp_date);
    ~Product();

    static uint16_t getProductsNumber() { return m_productsNumber; }

    std::string name;
private:
    static uint16_t m_productsNumber;
    uint8_t m_expiryDate;
};

struct Ingredient {
    Ingredient(Product& prod, Amount amnt) : product(prod), amount(amnt) {}
    Ingredient(const Product& prod, const Amount amnt) : product(prod), amount(amnt) {}

    Product product;
    Amount amount;
};

std::ostream& operator<<(std::ostream& out, const Ingredient& ingredient);

#endif //OPERATIONALRESEARCHAPP_INGREDIENT_H
