#include "model.h"

int main(int argc, char** argv) {
    std::cout << "Testing json" << std::endl;
    Model model;
    model.loadModel("../generated_data.json");  // todo: put into cli
}
