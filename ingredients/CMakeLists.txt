add_library(
        Ingredients
        src/ingredients/ingredient.cpp
        src/ingredients/ingredient.h
)

target_include_directories(Ingredients PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
