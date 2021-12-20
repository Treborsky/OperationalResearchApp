#include "model.h"

int main(int argc, char** argv) {
    std::string file_path;
    AppData data;

    file_path = "../sample_data/sandwich.csv";
    data.loadData(file_path);

    std::cout << "Data loaded without error, printing loaded data: " << std::endl << data;
    std::vector<bool> recipes = randomSolution(3); // this has got to be the same size as the vector of recipes
    std::cout << recipes[0] << recipes[1] << recipes[2] << std::endl;
    CostFunctionParams params(1.0, 1.0, 1.0); // those get normalized in the constructor

    Solution random_solution(data, recipes, 5, 50);

    std::cout << "Cost function for the random solution: " << random_solution.costFunction(params) << std::endl;

    int total_true = 0, total_false = 0;
    double percentage_true = 0.0;
    for(int i = 0; i < 10000; ++i) {
        std::vector<bool> random_bools = randomSolution(100);
        int count_true = 0, count_false = 0;

        //std::cout << "totally random randomizer test:" << std::endl;
        for(int i = 0; i < 100; ++i) {
            random_bools[i] ? count_true++: count_false++;
        }
        //std::cout << "Total: " << count_false + count_true << "\nFalse:\t" << count_false << "\nTrue:\t" << count_true << std::endl;
        total_true += count_true;
        total_false += count_false;
    }
    percentage_true = (double)total_true / (double)(total_false + total_true) * 100;
    std::cout << "Totals:\n" << total_true << " T - " << total_false << " F - " << percentage_true << "% True" << std::endl;
}
