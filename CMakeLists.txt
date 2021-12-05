cmake_minimum_required(VERSION 3.20)
project(OperationalResearchApp)
set(CMAKE_CXX_STANDARD 20)

# adding subdirectories that contain libraries
add_subdirectory(utility)
add_subdirectory(data_types)

# adding subdirectory with the main function
add_subdirectory(app)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
