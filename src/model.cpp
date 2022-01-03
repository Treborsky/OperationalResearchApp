//
// Created by User on 14.11.2021.
//

#include "model.h"

// Allocates memory and loads data from the .json file passed into the constructor
// Assumes a file format equivalent to the one generated from data_gen.py script included in the package
void Model::loadModel(const std::string& file_path) {
    std::ifstream i(file_path);
    json json_file;
    i >> json_file; // reading file as json

    m_n = json_file["n"];
    m_m = json_file["m"];

    m_X.reserve(m_n);
    for(auto& solution : m_X) {
        solution.reserve(m_m);
    }

    m_R = json_file["recipes"].get<Matrix2>();
    m_T = json_file["times"].get<VectorInt>();
    m_Q = json_file["quantities"].get<VectorInt>();
    m_E = json_file["dates"].get<VectorInt>();
    m_P = json_file["prices"].get<VectorInt>();
}

void Model::generateInitialSolution() {
    VectorBool initial_solution;
    initial_solution.reserve(m_n);
    for (int i = 0; i < m_n; ++i) {
        initial_solution[i] = randomBoolGenerator(gen);
    }
    m_X[0] = std::move(initial_solution);
}

void Model::generateNewSolution() {
    return VectorBool{};
}
