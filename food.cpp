#include "food.h"
#include "logic.h"
#include <iostream>

std::vector<double> food::get_food_location()
{
    return foodLocation;
}

int food::get_size_of_food()
{
    return foodSize;
}

void food::food_eaten()
{
    foodSize--;

    if(foodSize < foodSmallestSize)
        generate_new_food_location(gridSize);
}

void food::generate_new_food_location(int gridsize)
{
    gridSize = gridsize;
    foodSize = startingFoodSize;
    foodLocation[0] = logic::generate_random_double(0,gridSize-startingFoodSize);
    foodLocation[1] = logic::generate_random_double(0,gridSize-startingFoodSize);

}
