#include "gtest/gtest.h"
#include "food.h"
#include "world.h"

#define TOLERANCE .01

class WorldSpy: public world
{
public:

    std::vector<double> get_colony() {return colony;}
    int get_grid_size() {return gridSize;}
    std::vector<ant> &get_ants() {return antType;}
    std::vector<pheromone> &get_pheromones() {return pheromoneType;}
    food &get_food_class() {return foodType;}
};

class FoodSpy: public food
{
public:
    std::vector<double> get_food_position() {return foodLocation;}
    int get_food_size() {return foodSize;}
};

class FoodInstance:public testing::Test
{
public:
    FoodInstance()
    {
        foodStartingSize = foodType.get_size_of_food();
    }

protected:
    FoodSpy foodType;
    int foodStartingSize;
};

TEST_F(FoodInstance, givenAWorld_checkThatWhenTheFoodEatenFunctionIsTriggered_ThatTheFoodSizeDecreases)
{

    foodType.food_eaten();

    int foodEndingSize = foodType.get_size_of_food();
    int expectedFoodEndingSize{foodStartingSize-1};

    EXPECT_NE(foodStartingSize,foodEndingSize);
    EXPECT_EQ(foodEndingSize, expectedFoodEndingSize);
}

TEST_F(FoodInstance, givenAWorld_checkThatWhenFoodIsCompletelyEaten_ThatItRespawnsInANewLocation)
{

    std::vector<double> startingLocation{foodType.get_food_location()};
    double foodStartingSize = foodType.get_size_of_food();

    for(int i = 0; i < foodStartingSize; i++)
        foodType.food_eaten();

    std::vector<double> endingLocation{foodType.get_food_location()};

    EXPECT_NE(startingLocation,endingLocation);
}
