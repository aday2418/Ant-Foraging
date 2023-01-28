#include "gtest/gtest.h"
#include "world.h"

#define TOLERANCE .001

class WorldSpy: public world
{
public:

    std::vector<double> get_colony() {return colony;}
    int get_grid_size() {return gridSize;}
    std::vector<ant> &get_ants() {return antType;}
    std::vector<pheromone> &get_pheromones() {return pheromoneType;}
    food &get_food_class() {return foodType;}
};

class WorldInstance:public testing::Test
{
public:
    WorldInstance()
    {
        std::vector<double> colony = worldClass.get_colony();
    }

protected:
    WorldSpy worldClass;
    food foodType;
    int gridSize{worldClass.get_grid_size()};
    double colonyX;
    double colonyY;
};

TEST_F(WorldInstance, givenANewInstanceOfWorld_VerifyThatGenerateColonyAssignsValidXandYCoordinatesForTheColony)
{
    worldClass.generate_colony();
    std::vector<double> colony = worldClass.get_colony();

    double expectedLowerBound = 0;
    double expectedUpperBound = worldClass.get_grid_size();

    EXPECT_GE(colony[0],expectedLowerBound);
    EXPECT_GE(colony[1], expectedLowerBound);
    EXPECT_LE(colony[0], expectedUpperBound);
    EXPECT_LE(colony[1], expectedUpperBound);
}

TEST_F(WorldInstance, givenANewInstanceOfWorld_VerifyThatTheGenerateFoodFunctionAssignesValidStartingCoordinatesForFood)
{
    worldClass.generate_food();

    double expectedLowerBound = 0;
    double expectedUpperBound = worldClass.get_grid_size();

    EXPECT_GE(worldClass.get_food().at(0), expectedLowerBound);
    EXPECT_GE(worldClass.get_food().at(1), expectedLowerBound);
    EXPECT_LE(worldClass.get_food().at(0), expectedUpperBound);
    EXPECT_LE(worldClass.get_food().at(1), expectedUpperBound);
}

TEST_F(WorldInstance, givenAWorld_checkThatWhenTheFoodEatenFunctionIsTriggered_ThatTheFoodSizeDecreases)
{

    double foodStartingSize = foodType.get_size_of_food();

    foodType.food_eaten();

    double foodEndingSize = foodType.get_size_of_food();
    double expectedFoodEndingSize{foodStartingSize-1};

    EXPECT_NE(foodStartingSize,foodEndingSize);
    EXPECT_EQ(foodEndingSize, expectedFoodEndingSize);
}

TEST_F(WorldInstance, givenAWorldWith_Ants_IfUpdateIsCalled_CheckThatAntsMove)
{
    std::vector<ant> &antType{worldClass.get_ants()};

    for(int i = 0; i < antType.size(); i++)
    {
        std::vector<double> antInitialPosition{antType[i].get_current_position()};
        worldClass.update_values();
        std::vector<double> antFinalPosition{antType[i].get_current_position()};

        EXPECT_NE(antInitialPosition[0],antFinalPosition[0]);
    }
}

TEST_F(WorldInstance, givenAWorld_CheckToMakeSureThatWhenCreatingA1DVectorOfPointsThatTheVectorIsInitializedToTheCorrectSize)
{
    std::vector<int> oneDimensionalVector{worldClass.create_a_1d_vector_of_grid_size()};
    int sizeOfVector{0};

    for(int i = 0; i < oneDimensionalVector.size(); i++)
        sizeOfVector++;

    int expectedVectorSize{worldClass.get_grid_size()*worldClass.get_grid_size()};

    EXPECT_EQ(sizeOfVector,expectedVectorSize);
}

TEST_F(WorldInstance, givenThatFoodShrinksToLessThanTheTolerance_CheckThatFoodRespawnsInNewLocation)
{
    std::vector<double> foodStartingPosition{foodType.get_food_location()};
    int initialSizeOfFood{foodType.get_size_of_food()};

    for(int i = 0; i < initialSizeOfFood; i++)
        foodType.food_eaten();

    std::vector<double> foodEndingPosition{foodType.get_food_location()};

    EXPECT_NE(foodStartingPosition, foodEndingPosition);
}

TEST_F(WorldInstance, makeSureThatGetVectorOfPheromonesFunction_CorrectlyReturnsCorrectSizedVectorOfAllPheromonesInGrid)
{
    std::vector<int> vectorOfPheromones(gridSize*gridSize,0);
    std::vector<int> actualVectorOfPheromones{worldClass.get_vector_of_pheromone_levels()};

    EXPECT_EQ(vectorOfPheromones.size(), actualVectorOfPheromones.size());
}
