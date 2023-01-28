#include "gtest/gtest.h"
#include "pheromone.h"

class PheromoneSpy: public pheromone
{
public:
    int get_pheromone_level() {return level;}
    bool to_home() {return toHome;}
};

class PheromoneInstance:public testing::Test
{
public:
    PheromoneInstance()
    {
        pheromoneClass.set_location(startingLocation);
    }

protected:
    PheromoneSpy pheromoneClass;
    int startingLocation{12};
};

TEST_F(PheromoneInstance, makeSureThatIncrementLevelTurnsOnAPheromone)
{
    double distanceFromColony{0};
    pheromoneClass.increment_pheremone_level(distanceFromColony);

    int endingLevel{pheromoneClass.get_pheromone_level()};
    int expectedEndingLevel{300};

    EXPECT_EQ(endingLevel, expectedEndingLevel);
}

TEST_F(PheromoneInstance, makeSureThatDecrementLevel_DoesntDoAnythingIfPheromoneLevelIsAlreadyZero)
{
    pheromoneClass.decrement_pheromone_level();

    int endingLevel{pheromoneClass.get_pheromone_level()};
    int expectedEndingLevel{0};

    EXPECT_EQ(endingLevel, expectedEndingLevel);
}

TEST_F(PheromoneInstance, makeSureThatDecrementLevel_LessensPheromoneLevelByOne)
{
    double distanceFromColony{0};
    pheromoneClass.increment_pheremone_level(distanceFromColony);
    pheromoneClass.decrement_pheromone_level();

    int endingLevel{pheromoneClass.get_pheromone_level()};
    int expectedEndingLevel{299};

    EXPECT_EQ(endingLevel, expectedEndingLevel);
}

TEST_F(PheromoneInstance, makeSureThatThePheromoneLevelDroppedDecreasesWithIncreasingDistanceFromTheColony)
{
    double distanceFromColony{5};
    pheromoneClass.increment_pheremone_level(distanceFromColony);

    int endingLevel{pheromoneClass.get_pheromone_level()};
    int expectedEndingLevel{297};

    EXPECT_EQ(endingLevel, expectedEndingLevel);
}

