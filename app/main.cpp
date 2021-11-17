#include <iostream>
#include <model/model.h>

int main() {
    std::cout << "Hello program" << std::endl;
    // 1 initialize the data -> recipes, data_types, etc.
    AppData data;
    std::string filePath = "../../sample_data/sandwich.csv";    // using relative for development TODO: put it into cli
    data.loadData(filePath);
    std::cout << "Data loaded without error, printing loaded data: " << std::endl;
    std::cout << data;
    std::vector<bool> recipes;
    recipes.reserve(1);
    recipes.push_back(true);
    CostFunctionParams params(1.0, 1.0, 1.0);
    Solution randomSolution(data, recipes, 2, 50);
    std::cout << "Cost function for the random solution: " << randomSolution.costFunction(params) << std::endl;
    // 2 await the task
    // 3 if task is exit
    // 4 exit the app
    // 5 calculate the task
        // 5.1 envoke the algorythm
        // 5.2 display the output, log the output
    // 6 go to 2
}
