#include <ingredients/ingredient.h>
#include <recipes/recipe.h>

#include <iostream>
#include <vector>

void placeholder_main() {
    // 1 initialize some hardcoded recipes
    const Product bread("Bread", 3);
    const Product ham("Ham", 1);
    const Product butter("Butter", 7);
    const Product tea("Tea", 30);

    const Ingredient Bread(bread, 1);
    const Ingredient Ham(ham, 3);
    const Ingredient Butter(butter, 200);
    const Ingredient Tea(tea, 25);

    std::vector<Ingredient> sandwichIngredients;
    sandwichIngredients.reserve(3);
    sandwichIngredients.push_back(Ham);
    sandwichIngredients.push_back(Butter);
    sandwichIngredients.push_back(Bread);

    Recipe sandwichRecipe(sandwichIngredients, "ham sandwich", 5);
    // 2 print out all defined  products, ingredients and recipes

    std::cout << sandwichRecipe << std::endl;
    // output stuff
}

int main() {
    placeholder_main();
    // 1 initialize the data -> recipes, ingredients, etc.
    // 2 await the task
    // 3 if task is exit
    // 4 exit the app
    // 5 calculate the task
        // 5.1 envoke the algorythm
        // 5.2 display the output, log the output
    // 6 go to 2
}
