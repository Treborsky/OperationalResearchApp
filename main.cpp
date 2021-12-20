#include "model.h"

int main(int argc, char** argv) {
    std::string filePath;
    AppData data;

    filePath = "../sample_data/sandwich.csv";
    data.loadData(filePath);

    std::cout << "Data loaded without error, printing loaded data: " << std::endl << data;
    std::vector<bool> recipes(3); // this has got to be the same size as the vector of recipes

    CostFunctionParams params(1.0, 1.0, 1.0); // those get normalized in the constructor

    Solution randomSolution(data, recipes, 5, 50);

    std::cout << "Cost function for the random solution: " << randomSolution.costFunction(params) << std::endl;
}
