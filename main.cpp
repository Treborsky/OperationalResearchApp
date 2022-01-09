//
// Created by Robert Koziarski on 09.11.2021.
//

#include "model.h"

NeighborhoodType interpret_nbr_select_type(int);
inline SolutionSelectionMethod interpret_ssm_select_type(int);

int main() {
    Model model = Model();

    std::cout << "Hardcoded model loaded. Insert parameters to run optimization" << std::endl;

    double a, b, g;
    std::cout << "[double] alpha: ";
    std::cin >> a;
    std::cout << "[double] beta: ";
    std::cin >> b;
    std::cout << "[double] gamma: ";
    std::cin >> g;
    model.set_params(a, b, g);

    std::cout << std::endl << "Now select neighbourhood selection method" << std::endl;
    std::cout << neighbourhood_select_menu << "Selection: ";
    int select;
    std::cin >> select;

    std::cout << std::endl << "Now select solution selection method" << std::endl;
    std::cout << ssm_select_menu << "Selection: ";
    int select2;
    std::cin >> select2;

    std::cout << "Insert max iterations: ";
    int iter;
    std::cin >> iter;
    std::cout << "Insert cost function cutoff: ";
    double cutoff;
    std::cin >> cutoff;
    int nbrhd_size;
    std::cout << "Insert neighborhood size: ";
    std::cin >> nbrhd_size;
    std::cout << "Data complete" << std::endl;

    NeighborhoodType nbr_type = interpret_nbr_select_type(select);
    SolutionSelectionMethod ssm_type = interpret_ssm_select_type(select2);
    std::cout << std::endl << "Calling Taboo Search algorythm..." << std::endl;
    model.tabooSearch(iter, nbr_type, ssm_type, cutoff, nbrhd_size);
}


NeighborhoodType interpret_nbr_select_type(int select) {
    NeighborhoodType type;
    switch (select) {
        case 1:
            type = HAM2;
            break;
        case 2:
            type = HAM3;
            break;
        case 3:
            type = HAM4;
            break;
        case 4:
            type = RAND;
            break;
        default:
            type = HAM2;
    }
    return type;
}

inline SolutionSelectionMethod interpret_ssm_select_type(int select) {
    if (select == 2) return RANDOM;
    else return BEST;
}