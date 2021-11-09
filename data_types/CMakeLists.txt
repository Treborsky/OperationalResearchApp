add_library(
        DataTypes
        src/ingredients/ingredient.cpp
        src/ingredients/ingredient.h
        src/recipes/recipe.cpp
        src/recipes/recipe.h
        src/supplies/supply.cpp
        src/supplies/supply.h
)

target_include_directories(DataTypes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(DataTypes PUBLIC Utility)
