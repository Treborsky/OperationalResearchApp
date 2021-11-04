add_library(
        Recipes
        src/recipes/recipe.cpp
        src/recipes/recipe.h
)

target_include_directories(Recipes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Recipes PRIVATE Ingredients)