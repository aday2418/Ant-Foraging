#include "gtest/gtest.h"
#include "ant.h"
#include "world.h"
#include "logic.h"
#include "food.h"

#define TOLERANCE .01

class WorldSpy: public world
{
public:
    std::vector<double> get_colony() {return colony;}
    int get_grid_size() {return gridSize;}
    int get_ant_size() {return antSize;}
};

class AntSpy: public ant
{
public:
    std::vector<double> get_current_position() {return currentPosition;}
    double get_variation_range() {return variationRange;}
    double get_variation() {return variation;}
};

class AntInstance:public testing::Test
{
public:
    AntInstance()
    {
        antClass.set_starting_point(worldClassForAnt.get_colony(),worldClassForAnt.get_grid_size(),worldClassForAnt.get_colony_size());
        std::vector<double> colony = antClass.get_current_position();
    }

protected:
    AntSpy antClass;
    WorldSpy worldClassForAnt;
    double antX;
    double antY;
    int gridSize{worldClassForAnt.get_grid_size()};
    int colonySize{worldClassForAnt.get_colony_size()};
    double grid = gridSize;
    int startingSize{1};
};

TEST_F(AntInstance, givenANewInstanceOfAnt_VerifyThatTheContructorAssignsValidOrientation)
{
    double expectedLowerBound = 0;
    double expectedUpperBound = 360 + TOLERANCE;

    EXPECT_LE(expectedLowerBound, antClass.get_orientation());
    EXPECT_GE(expectedUpperBound, antClass.get_orientation());
}

TEST_F(AntInstance, givenANewInstanceOfAnt_VerifyThatAntSetStartingPointCorrectlyAssignsAStartingPointInTheCenterOfTheColony)
{
    std::vector<double> antPosition{antClass.get_current_position()};
    std::vector<double> colonyPosition{worldClassForAnt.get_colony()};

    colonyPosition[0] += worldClassForAnt.get_colony_size()/2;
    colonyPosition[1] += worldClassForAnt.get_colony_size()/2;

    EXPECT_EQ(antPosition.at(0),colonyPosition.at(0));
    EXPECT_EQ(antPosition.at(1),colonyPosition.at(1));
}

TEST_F(AntInstance, givenAnInstanceOfAnt_CheckThatWhenSettingTheOrientation_ThatTheConversionBetweenDegreesAndRadiansIsWithinTolerance)
{
    double inputDegreeVal{200};
    antClass.set_orientation(200);
    double returnedDegreeVal{antClass.get_orientation()};

    EXPECT_NEAR(inputDegreeVal,returnedDegreeVal, TOLERANCE);
}

TEST_F(AntInstance, givenAnInstaceOfAnt_CheckThatAfterCallingStep_ThatTheAntPostionChanges)
{
    double originalPositionX = antClass.get_current_position().at(0);
    double originalPositionY = antClass.get_current_position().at(1);

    antClass.step();

    double newPositionX = antClass.get_current_position().at(0);
    double newPositionY = antClass.get_current_position().at(1);

    EXPECT_NE(originalPositionX, newPositionX);
    EXPECT_NE(originalPositionY, newPositionY);
}

TEST_F(AntInstance, givenAnInstanceOfAnt_CheckThatAfterCallingWanderAndTakingAStepThatTheAntCorrectlyFollowsTheAssignedOrientation)
{
    double expectedAngle{45};

    std::vector<double> originalPosition{antClass.get_current_position()};
    antClass.set_orientation(expectedAngle);
    antClass.wander();

    for(int i = 0; i < 5; i++)
        antClass.step();

    int finalPosition{logic::convert_from_x_y_double_coordinates_to_i_value(antClass.get_current_position(), gridSize)};

    double tolerance = antClass.get_variation_range() * 2 * 58 + worldClassForAnt.get_ant_size()/2;
    double actualAngle{logic::calculate_new_angle(originalPosition,finalPosition,gridSize)};

    EXPECT_NEAR(expectedAngle, actualAngle, tolerance);
}

TEST_F(AntInstance, checkThatWhenAssigningAnOrientationThatIsNegative_ThatWhenYouGetTheOrientationThatItIsReturnedAsAPositiveNumberFromZeroToThreeHundredSixty)
{
    double expectedOrientation{348};
    antClass.set_orientation(-12);
    double actualOrientation{antClass.get_orientation()};

    EXPECT_NEAR(expectedOrientation, actualOrientation, TOLERANCE);
}

TEST_F(AntInstance, checkThatWhenAssigningAnOrientationThatIsGreaterThanThreeHundredSixty_ThatWhenYouGetTheOrientationThatItIsReturnedAsAPositiveNumberFromZeroToThreeHundredSixty)
{
    double expectedOrientation{140};
    antClass.set_orientation(500);
    double actualOrientation{antClass.get_orientation()};

    EXPECT_NEAR(expectedOrientation, actualOrientation, TOLERANCE);
}

TEST_F(AntInstance, ifAnAntIsPlacedAtTheEdgeOfTheGridAndWanderIsCalled_AssureThatTheAntStaysWithinTheGrid_EvenIfWanderIsCalledRepetitively)
{
    std::vector<double> startingPoint{grid-1, grid/2};

    antClass.set_starting_point(startingPoint,gridSize,startingSize);

    int numLoops{5};
    double lowerBoundX = -worldClassForAnt.get_ant_size();
    double lowerBoundY = -worldClassForAnt.get_ant_size();
    double upperBoundX = worldClassForAnt.get_grid_size() + worldClassForAnt.get_ant_size();
    double upperBoundY = worldClassForAnt.get_grid_size() + worldClassForAnt.get_ant_size();

    for(int i = 0; i < numLoops; i++)
    {
        antClass.wander();

        double newPositionX = antClass.get_current_position().at(0);
        double newPositionY = antClass.get_current_position().at(1);

        EXPECT_LE(newPositionX, upperBoundX);
        EXPECT_LE(newPositionY, upperBoundY);
        EXPECT_GE(newPositionX, lowerBoundX);
        EXPECT_GE(newPositionY, lowerBoundY);
    }
}

TEST_F(AntInstance, testThatTheDistanceAnAntHasTraveledFromTheColonyIsAccuratelyCaluculated)
{
    std::vector<double> startingPoint{10, 10};
    antClass.set_starting_point(startingPoint,gridSize,startingSize);
    std::vector<double> colonyLocation{7,6};

    double expectedDistance{5};
    double actualDistance = antClass.calculate_distance_from_colony(colonyLocation);
    double toleranceDueToIntRounding{1.5};

    EXPECT_NEAR(expectedDistance, actualDistance, toleranceDueToIntRounding);
}

TEST_F(AntInstance, testThatWhenGivenAnOrientationThatTheCorrectSampleOfPointsIsCreated)
{
    antClass.set_sample_size(2);
    std::vector<int> iPointsToSample{0};
    std::vector<double> location{10,10};

    antClass.set_starting_point(location,gridSize,colonySize);
    antClass.set_orientation(10);
    std::vector<double> currentPosition{antClass.get_current_position()};

    antClass.sample_in_direction_of_orientation(iPointsToSample);
    std::vector<int> expectedSample{23661, 24061, 23662, 24062};

    EXPECT_EQ(iPointsToSample,expectedSample);
}

TEST_F(AntInstance, testThatWhenALlPheromonesAre0InASampleThatTheAntsOrientationIsNotChanged)
{
    std::vector<int> levels(100,0);
    std::vector<bool> toHome(100,false);
    worldClassForAnt.generate_pheromones();
    food foodClass;

    double orientationBefore{antClass.get_orientation()};
    antClass.reorient_towards_pheromones(levels,toHome,foodClass);
    double orientationAfter{antClass.get_orientation()};

    EXPECT_EQ(orientationBefore,orientationAfter);
}

TEST_F(AntInstance, testThatWhenAPheromeInASampleIsDetectedToBeTheHighestLevelThatTheAntsOrientationIsChanged)
{
    std::vector<int> levels(200000,500);
    std::vector<bool> toHome(200000,false);
    food foodClass;

    double orientationBefore{antClass.get_orientation()};
    antClass.reorient_towards_pheromones(levels,toHome,foodClass);
    double orientationAfter{antClass.get_orientation()};

    EXPECT_NE(orientationBefore,orientationAfter);
}

