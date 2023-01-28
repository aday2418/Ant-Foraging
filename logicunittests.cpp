#include "gtest/gtest.h"
#include "logic.h"

#define TOLERANCE .01

TEST(logic, testThatMyRandomDoubleFunctionActuallyGeneratesRandomNumbersWithinTheBoundariesSpecified)
{
    double lowerBoundary{0};
    double upperBoundary{1000};

    double double1{logic::generate_random_double(lowerBoundary,upperBoundary)};
    double double2{logic::generate_random_double(lowerBoundary,upperBoundary)};

    if(double1 >= lowerBoundary && double2 >= lowerBoundary && double1 <= upperBoundary && double2 <= upperBoundary)
        EXPECT_NE(double1, double2);
}

TEST(logic, testThatTheFunction_ConvertFromXYCoordinatesToIValue_ProperlyConvertsFrom2Dto1DCoordinates)
{
    std::vector<double> xyCoordinates {3,2};
    int gridSize{5};

    int expectedOutput{13};
    int actualOutput = logic::convert_from_x_y_double_coordinates_to_i_value(xyCoordinates,5);

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(logic, testThatTheFunction_ConvertFromIValueToXYCoordinates_ProperlyConvertsFrom1Dto2DCoordinates)
{
    int iValue{16};
    int gridSize{5};

    std::vector<double> expectedOutput{1,3};
    std::vector<double> actualOutput{logic::convert_from_i_value_to_x_y_coordinates(iValue,gridSize)};

    EXPECT_EQ(expectedOutput.at(0), actualOutput.at(0));
    EXPECT_EQ(expectedOutput.at(1), actualOutput.at(1));
}

TEST(logic, testThatTheFunction_CreateAVectorOfAllIValuesToPaint_ProperlyCreatesA1DVectorOfPointsFromAnInitial1DStartingPoint)
{
    int iValue{12};
    int gridSize{5};
    int paintSize{2};

    std::vector<int> expectedOutput{12,17,13,18};
    std::vector<int> actualOutput{logic::create_vector_of_all_i_values_to_paint(iValue,paintSize,gridSize)};

    for(int i = 0; i < 4; i++)
        EXPECT_EQ(expectedOutput.at(0), actualOutput.at(0));
}

TEST(logic, testThatTheFunction_CreateAVectorOfAllIValuesToPaint_ProperlyCreatesA1DVectorOfPointsFromAnInitialStartingPoint_WithABiggerGridAndPaintSize)
{
    int iValue{22};
    int gridSize{10};
    int paintSize{4};

    std::vector<int> expectedOutput{22,32,42,52,23,33,43,53,24,34,44,54,45,35,45,55};
    std::vector<int> actualOutput{logic::create_vector_of_all_i_values_to_paint(iValue,paintSize,gridSize)};

    for(int i = 0; i < 4; i++)
        EXPECT_EQ(expectedOutput.at(0), actualOutput.at(0));
}

TEST(logic, testThatWhenSamplingRight_ThatASmallChunkOfTheGridIsAnalyzed_andThatTheCorrectValuesToTheRightAreSampled)
{
    int gridSize{10};
    double antXPosition{2.1};
    double antYPosition{5.3};
    int sampleSize{4};

    std::vector<int> expectedOutput{33,43,53,63,34,44,54,64,35,45,55,65,36,46,56,66};
    std::vector<int> actualOutput{logic::sample_right(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingRightThatOutOfBoundsValuesAreNotReturned)
{
    int gridSize{10};
    double antXPosition{5};
    double antYPosition{1};
    int sampleSize{4};

    std::vector<int> expectedOutput{6,16,26,7,17,27,8,18,28,9,19,29};
    std::vector<int> actualOutput{logic::sample_right(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingLeft_ThatASmallChunkOfTheGridIsAnalyzed_andThatTheCorrectValuesToTheLeftAreSampled)
{
    int gridSize{10};
    double antXPosition{5.1};
    double antYPosition{5.3};
    int sampleSize{4};

    std::vector<int> expectedOutput{31,41,51,61,32,42,52,62,33,43,53,63,34,44,54,64};
    std::vector<int> actualOutput{logic::sample_left(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingLeftThatOutOfBoundsValuesAreNotReturned)
{
    int gridSize{10};
    double antXPosition{8};
    double antYPosition{1};
    int sampleSize{4};

    std::vector<int> expectedOutput{4,14,24,5,15,25,6,16,26,7,17,27};
    std::vector<int> actualOutput{logic::sample_left(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingUp_ThatASmallChunkOfTheGridIsAnalyzed_andThatTheCorrectValuesUpAreSampled)
{
    int gridSize{10};
    double antXPosition{4.1};
    double antYPosition{6.3};
    int sampleSize{4};

    std::vector<int> expectedOutput{22,32,42,52,23,33,43,53,24,34,44,54,25,35,45,55};
    std::vector<int> actualOutput{logic::sample_up(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingUpThatOutOfBoundsValuesAreNotReturned)
{
    int gridSize{10};
    double antXPosition{7};
    double antYPosition{2};
    int sampleSize{4};

    std::vector<int> expectedOutput{5,15,6,16,7,17,8,18};
    std::vector<int> actualOutput{logic::sample_up(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingDown_ThatASmallChunkOfTheGridIsAnalyzed_andThatTheCorrectValuesDownAreSampled)
{
    int gridSize{10};
    double antXPosition{4.1};
    double antYPosition{3.3};
    int sampleSize{4};

    std::vector<int> expectedOutput{42,52,62,72,43,53,63,73,44,54,64,74,45,55,65,75};
    std::vector<int> actualOutput{logic::sample_down(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, testThatWhenSamplingDownThatOutOfBoundsValuesAreNotReturned)
{
    int gridSize{10};
    double antXPosition{4};
    double antYPosition{7};
    int sampleSize{4};

    std::vector<int> expectedOutput{82,92,83,93,84,94,85,95};
    std::vector<int> actualOutput{logic::sample_down(sampleSize,antXPosition,antYPosition,gridSize)};

    for(int i = 0; i < actualOutput.size(); i++)
        EXPECT_EQ(expectedOutput.at(i),actualOutput.at(i));
}

TEST(logic, givenAWorld_checkThatWhenGettingThePositionOfTheHighestPheromoneLevel_ThatTheCorrectPositionIsReturned)
{
    bool hasFood = false;
    std::vector<int> iPositions{32,42,52,62,33,43,53,63,34,44,54,64,35,45,55,65};
    std::vector<int> pheromoneLevels(100,0);
    std::vector<bool> toHome(iPositions.size(),true);

    pheromoneLevels[52] = 402;
    pheromoneLevels[63] = 410;
    pheromoneLevels[80] = 490;

    int expectedOutput{63};
    int actualOutput{logic::get_position_of_highest_pheromone_level(hasFood, iPositions, pheromoneLevels, toHome)};

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(logic, testThatWhenCalculatingANewOrientation_ThatTheAngleBetweenTheCurrentAndFinalPositionIsCorrectlyCalculatedInDegreesForFourthQuadrent)
{
    int gridSize{10};
    std::vector<double> currentPosition{2.0,6.0};
    int iCoordinate{35};

    double expectedAngle{-45};
    double actualAngle{logic::calculate_new_angle(currentPosition,iCoordinate,gridSize)};

    EXPECT_NEAR(expectedAngle, actualAngle, TOLERANCE);
}

TEST(logic, testThatWhenCalculatingANewOrientation_ThatTheAngleBetweenTheCurrentAndFinalPositionIsCorrectlyCalculatedInDegreesForFirstQuadrent)
{
    int gridSize{10};
    std::vector<double> currentPosition{2.0,6.0};
    int iCoordinate{95};

    double expectedAngle{45};
    double actualAngle{logic::calculate_new_angle(currentPosition,iCoordinate,gridSize)};

    EXPECT_NEAR(expectedAngle, actualAngle, TOLERANCE);
}

TEST(logic, testThatWhenCalculatingANewOrientation_ThatTheAngleBetweenTheCurrentAndFinalPositionIsCorrectlyCalculatedInDegreesForThirdQuadrent)
{
    int gridSize{10};
    std::vector<double> currentPosition{5.0,6.0};
    int iCoordinate{32};

    double expectedAngle{-135};
    double actualAngle{logic::calculate_new_angle(currentPosition,iCoordinate,gridSize)};

    EXPECT_NEAR(expectedAngle, actualAngle, TOLERANCE);
}

TEST(logic, testThatWhenCalculatingANewOrientation_ThatTheAngleBetweenTheCurrentAndFinalPositionIsCorrectlyCalculatedInDegreesForSecondQuadrent)
{
    int gridSize{10};
    std::vector<double> currentPosition{5.0,3.0};
    int iCoordinate{62};

    double expectedAngle{135};
    double actualAngle{logic::calculate_new_angle(currentPosition,iCoordinate,gridSize)};

    EXPECT_NEAR(expectedAngle, actualAngle, TOLERANCE);
}

TEST(logic, testThatWhenCalculatingIfTwoObjectsIntersectThatTheTrueIsReturnedIfTheyDoIntersect)
{
    std::vector<double> antPosition{105,25};
    int antSize{2};
    std::vector<double> foodPosition{100,20};
    int foodSize{100};

    bool intersection{logic::check_for_intersection(antPosition,antSize,foodPosition,foodSize)};

    EXPECT_EQ(true, intersection);
}

TEST(logic, testThatWhenCalculatingIfTwoObjectsIntersectThatFalseIsReturnedIfTheyDontIntersect)
{
    std::vector<double> antPosition{100,20};
    int antSize{2};
    std::vector<double> foodPosition{154,69};
    int foodSize{100};

    bool intersection{logic::check_for_intersection(antPosition,antSize,foodPosition,foodSize)};

    EXPECT_EQ(false, intersection);
}

TEST(logic, testThatWhenPassingInAnOrientationThatABoolOfIfTheDirectionIsFacingUpIsCorrectlyReturned)
{
    double orientation{300};

    bool expectedBool{true};
    bool actualBool{logic::facing_up(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAWrongOrientationThatABoolOfIfTheDirectionIsFacingUpIsCorrectlyReturnedAsFalse)
{
    double orientation{90};

    bool expectedBool{false};
    bool actualBool{logic::facing_up(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAnOrientationThatABoolOfIfTheDirectionIsFacingDownIsCorrectlyReturned)
{
    double orientation{100};

    bool expectedBool{true};
    bool actualBool{logic::facing_down(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAWrongOrientationThatABoolOfIfTheDirectionIsFacingDownIsCorrectlyReturnedAsFalse)
{
    double orientation{10};

    bool expectedBool{false};
    bool actualBool{logic::facing_down(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAnOrientationThatABoolOfIfTheDirectionIsFacingLeftIsCorrectlyReturned)
{
    double orientation{200};

    bool expectedBool{true};
    bool actualBool{logic::facing_left(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAWrongOrientationThatABoolOfIfTheDirectionIsFacingLeftIsCorrectlyReturnedAsFalse)
{
    double orientation{10};

    bool expectedBool{false};
    bool actualBool{logic::facing_left(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAnOrientationThatABoolOfIfTheDirectionIsFacingRightIsCorrectlyReturned)
{
    double orientation{5};

    bool expectedBool{true};
    bool actualBool{logic::facing_right(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatWhenPassingInAWrongOrientationThatABoolOfIfTheDirectionIsFacingRightIsCorrectlyReturnedAsFalse)
{
    double orientation{100};

    bool expectedBool{false};
    bool actualBool{logic::facing_right(orientation)};

    EXPECT_EQ(expectedBool,actualBool);
}

TEST(logic, testThatCreatingASampleVectorCorrectlyCreatesCopiesThePassedInVectorToTheVectorOfIPoints)
{
    std::vector<int> samplePoints{1,3,5,7,9,10};
    std::vector<int> iPoints{0};

    logic::create_sample_vector(iPoints,samplePoints);

    EXPECT_EQ(iPoints,samplePoints);
}

TEST(logic, checkThatANegativeOrientationIsCorrectlyConvertedToAnEquivalentPositiveValue)
{
    double orientation{-12};
    double expectedOrientation{348};

    double actualOrientation{logic::convert_to_positive_degree_value(orientation)};

    EXPECT_NEAR(expectedOrientation, actualOrientation, TOLERANCE);
}

TEST(logic, checkThatAnOrientationGreaterThan360IsCorrectlyConvertedToAnEquivalentPositiveValueGreaterThan0ButLessThan360)
{
    double orientation{380};
    double expectedOrientation{20};

    double actualOrientation{logic::convert_to_positive_degree_value(orientation)};

    EXPECT_NEAR(expectedOrientation, actualOrientation, TOLERANCE);
}
