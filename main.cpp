//
// Created by Robert Koziarski on 09.11.2021.
//

#include "model.h"

int main() {

    AppState state = MENU;
    Model model;

    while(state != QUIT) {
        switch (state) {
            case MENU: {
                clearConsole();
                std::cout << std::endl << menu_str;
                int new_state;
                std::cin >> new_state;
                switch (new_state) {
                    case 1:
                        state = FILE_SEL;
                        break;
                    case 2:
                        state = PARAM_SEL;
                        break;
                    case 3:
                        state = RESULT_VIEW;
                        break;
                    case 4:
                        state = CALCULATIONS;
                        break;
                    default:
                        state = QUIT;
                        break;
                }
                break;
            }
            case FILE_SEL: {
                std::cout << file_sel_str << "Insert relative file path: ";
                std::string file_path;
                std::cin >> file_path;
                // TODO: add regex to check if the file is in fact a .json on relative path
                try {
                    model.loadModel(file_path);
                } catch (std::exception& ex) {
                    std::cout << "Path to invalid file provided." << std::endl;
                }
                state = MENU;
                break;
            }
            case PARAM_SEL: {
                int alpha, beta, gamma;
                std::cout << param_sel_str << "alpha: ";
                std::cin >> alpha;
                std::cout << "beta: ";
                std::cin >> beta;
                std::cout << "gamma: ";
                std::cin >> gamma;
                state = MENU;
                break;
            }
            case RESULT_VIEW: {
                std::cout << result_view_str;
                // TODO: display results somehow
                // TODO: add the option to write stuff to a file
                std::cout << "Type 1 to write results into a file or any key to go back to menu" << std::endl;
                std::cout << "Input: ";
                int flag;
                std::cin >> flag;
                if (flag == 1) {
                    // TODO: write to file
                }
                state = MENU;
                break;
            }
            case CALCULATIONS: {
                std::cout << calculations_str;
                // TODO: perform optimization
                state = MENU;
                break;
            }
            default:
                state = QUIT;
                break;
        }
    }
}
