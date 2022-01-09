//
// Created by Robert Koziarski on 09.11.2021.
//

#include "utility.h"

void clearConsole() {
    std::cout << "\n========================================" << std::endl;
}

CostFunctionParams::CostFunctionParams(double a, double b, double g) { // normalization
    double sum = a + b + g;
    alpha = a / sum;
    beta = b / sum;
    gamma = g / sum;
}

bool TabooList::contains(int idx) const {
    return std::any_of(list_.begin(), list_.end(), [&](const auto& t){
        return t.first == idx;
    });
}

void TabooList::iterate() {
    std::vector<int> to_erase;
    for (int i = 0; i < size; ++i) {
        age_[i]--;
        if (!age_[i]) {
            to_erase.push_back(i);
        }
    }
    for (int i = 0; i < to_erase.size(); ++i) {
        list_.erase(i);
        age_.erase(i);
    }
}

void TabooList::add(int idx, Move mv, int memory_len) {
    if (!full) {
        list_.insert(std::make_pair(idx, mv));
        age_.insert(std::make_pair(idx, memory_len));
        size += 1;
        if (size == 50) full = true;
    }
}

void TabooList::remove(int idx) {
    list_.erase(idx);
    age_.erase(idx);
    size -= 1;
    if (size != 50) full = false;
}
