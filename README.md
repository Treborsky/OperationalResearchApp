# Kitchen manager app
An application that calculates the optimal purchases and cooking in order to minimize waste in the kitchen.

## Tech stack
### Business logic
 - C++ 20
 - CMake 3.20.2
 - Python 3.6 (random, json modules) (for data generation)

### Presentation
 - to be decided
 - TUI - terminal / text

## Notes
### Dimensions
 - N is the number of recipes
 - M is the number of ingredients
### R matrix
 - i (the row index) is also the RecipeID
 - R[ i ] is a vector containing ingredients
 - R[ i ][ j ] is the amount of j-th ingredient (0 if not used)
 - size is N x M
### X matrix
 - X[ i ] is a vector containing a single solution
 - X[ i ][ j ] is a boolean value indicating whether the given recipe will be used or not
 - size is <number_of_solutions / size_of_solution_space> x N
### T vector
 - T[ i ] is the preparation time for i-th recipe
 - size is 1 x N
### Q vector
 - Q[ j ] is the amount of j-th ingredient we have available
 - size is 1 x M
### E vector
 - E[ j ] is the expiration date of the j-th ingredient
 - size is 1 x M
### P vector
 - P[ j ] is the price of j-th ingredient
 - size is 1 x M
 
