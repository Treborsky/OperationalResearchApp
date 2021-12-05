#include <iostream>
#include <model/model.h>

int main(int argc, char** argv) {
    // 0 parse the input (only the data file)
    std::string filePath;
    if (argc) {
        // TODO: implement cli option to input a data file
    }

    // 1 initialize the data -> recipes, data_types, etc.
    AppData data;
    filePath = "../../sample_data/sandwich.csv";    // using relative for development TODO: put it into cli
    data.loadData(filePath);
    // std::cout << "Data loaded without error, printing loaded data: " << std::endl << data;

    std::vector<bool> recipes(3); // this has got to be the same size as the vector of recipes
    CostFunctionParams params(1.0, 1.0, 1.0); // those get normalized in the constructor
    Solution randomSolution(data, recipes, 5, 50);
    std::cout << "Cost function for the random solution: " << randomSolution.costFunction(params) << std::endl;
    // 2 await the task
    // 3 if task is exit
    // 4 exit the app
    // 5 calculate the task
        // 5.1 envoke the algorythm
        // 5.2 display the output, log the output
    // 6 go to 2
}
