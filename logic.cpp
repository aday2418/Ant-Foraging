#include "logic.h"
#include <random>
#include <iostream>
#include <cmath>

double logic::generate_random_double(double minValue, double maxValue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minValue, maxValue);
    return dis(gen);
}

int logic::convert_from_x_y_double_coordinates_to_i_value(std::vector<double> xyCoordinates, int gridSize)
{
    double xCoordinateDouble{xyCoordinates[0]};
    double yCoordinateDouble{xyCoordinates[1]};

    int xCoordinate = xCoordinateDouble;
    int yCoordinate = yCoordinateDouble;

    int iVal = xCoordinate + (yCoordinate*gridSize);

    return iVal;
}

std::vector<double> logic::convert_from_i_value_to_x_y_coordinates(int iVal, int gridSize)
{
    double yCoordinate = iVal/gridSize;
    double xCoordinate = iVal - yCoordinate*gridSize;
    std::vector<double> xyCoordinates{xCoordinate,yCoordinate};

    return xyCoordinates;
}

std::vector<int> logic::create_vector_of_all_i_values_to_paint(int iStartingValue, int paintSize, int gridSize)
{
    std::vector<int> vectorOfAllIValues(paintSize*paintSize,0);
    int index = 0;

    for(int i = iStartingValue; i < (iStartingValue + paintSize); i++)
        for(int j = 0; j < paintSize; j++)
        {
            vectorOfAllIValues[index] = i+j*gridSize;
            index++;
        }

    return vectorOfAllIValues;
}

std::vector<int> logic::sample_right(int sampleSize, double xPosition, double yPosition, int gridSize) //Make a test here
{
    std::vector<double> xPointsToSample(sampleSize*sampleSize,0); //I'm pretty sure this one worked <- come back + check + write test
    std::vector<double> yPointsToSample(sampleSize*sampleSize,0);
    std::vector<int> iPointsToSample;
    int index = 0;

    for(int i = 0; i < sampleSize; i++)
        for(int j = 0; j < sampleSize; j++)
        {
            double adjustedX = xPosition + 1;
            double adjustedY = yPosition - sampleSize/2;

            xPointsToSample[index] = adjustedX + i;
            yPointsToSample[index] = adjustedY + j;

            std::vector<double> vectorToPushIntoIPoints(2,0);
            vectorToPushIntoIPoints[0] = xPointsToSample[index];
            vectorToPushIntoIPoints[1] = yPointsToSample[index];

            int numberToPutInIPoints{logic::convert_from_x_y_double_coordinates_to_i_value(vectorToPushIntoIPoints,gridSize)};
            if(numberToPutInIPoints > 0 && numberToPutInIPoints < gridSize*gridSize)
                iPointsToSample.push_back(numberToPutInIPoints);

            index++;
        }

    return iPointsToSample;
}

std::vector<int> logic::sample_left(int sampleSize, double xPosition, double yPosition, int gridSize) //Make a test here
{
    std::vector<double> xPointsToSample(sampleSize*sampleSize,0);
    std::vector<double> yPointsToSample(sampleSize*sampleSize,0);
    std::vector<int> iPointsToSample;
    int index = 0;

    for(int i = 0; i < sampleSize; i++)
        for(int j = 0; j < sampleSize; j++)
        {
            double adjustedY = yPosition - sampleSize/2;
            double adjustedX = xPosition - sampleSize;

            xPointsToSample[index] = adjustedX + i;
            yPointsToSample[index] = adjustedY + j;

            std::vector<double> vectorToPushIntoIPoints(2,0);
            vectorToPushIntoIPoints[0] = xPointsToSample[index];
            vectorToPushIntoIPoints[1] = yPointsToSample[index];

            int numberToPutInIPoints{logic::convert_from_x_y_double_coordinates_to_i_value(vectorToPushIntoIPoints,gridSize)};
            if(numberToPutInIPoints > 0 && numberToPutInIPoints < gridSize*gridSize)
                iPointsToSample.push_back(numberToPutInIPoints);

            index++;
        }

    return iPointsToSample;
}

std::vector<int> logic::sample_up(int sampleSize, double xPosition, double yPosition, int gridSize)
{
    std::vector<double> xPointsToSample(sampleSize*sampleSize,0);
    std::vector<double> yPointsToSample(sampleSize*sampleSize,0);
    std::vector<int> iPointsToSample;
    int index = 0;

    for(int i = 0; i < sampleSize; i++)
        for(int j = 0; j < sampleSize; j++)
        {
            double adjustedY = yPosition - sampleSize;
            double adjustedX = xPosition - sampleSize/2;

            xPointsToSample[index] = adjustedX + i;
            yPointsToSample[index] = adjustedY + j;

            std::vector<double> vectorToPushIntoIPoints(2,0);
            vectorToPushIntoIPoints[0] = xPointsToSample[index];
            vectorToPushIntoIPoints[1] = yPointsToSample[index];

            int numberToPutInIPoints{logic::convert_from_x_y_double_coordinates_to_i_value(vectorToPushIntoIPoints,gridSize)};
            if(numberToPutInIPoints > 0 && numberToPutInIPoints < gridSize*gridSize)
                iPointsToSample.push_back(numberToPutInIPoints);

            index++;
        }

    return iPointsToSample;
}

std::vector<int> logic::sample_down(int sampleSize, double xPosition, double yPosition, int gridSize)
{
    std::vector<double> xPointsToSample(sampleSize*sampleSize,0);
    std::vector<double> yPointsToSample(sampleSize*sampleSize,0);
    std::vector<int> iPointsToSample;
    int index = 0;

    for(int i = 0; i < sampleSize; i++)
        for(int j = 0; j < sampleSize; j++)
        {
            double adjustedX = xPosition - sampleSize/2;
            double adjustedY = yPosition + 1;

            xPointsToSample[index] = adjustedX + i;
            yPointsToSample[index] = adjustedY + j;

            std::vector<double> vectorToPushIntoIPoints(2,0);
            vectorToPushIntoIPoints[0] = xPointsToSample[index];
            vectorToPushIntoIPoints[1] = yPointsToSample[index];

            int numberToPutInIPoints{logic::convert_from_x_y_double_coordinates_to_i_value(vectorToPushIntoIPoints,gridSize)};
            if(numberToPutInIPoints > 0 && numberToPutInIPoints < gridSize*gridSize)
                iPointsToSample.push_back(numberToPutInIPoints);

            index++;
        }

    return iPointsToSample;
}

int logic::get_position_of_highest_pheromone_level(bool antHasFood, std::vector<int> &iPositions, std::vector<int> &pheromoneLevels, std::vector<bool> &toHome) //Try to move this off the class later
{
    int highestPheromoneLevel{400};
    int highestPheromonePosition{0};

    for (int i = 0; i < iPositions.size(); i++)
        if(pheromoneLevels[iPositions[i]] > 1 && pheromoneLevels.at(iPositions[i]) > highestPheromoneLevel &&
                ((antHasFood == true && toHome[iPositions[i]] == true) ||
                 (antHasFood == false && toHome[iPositions[i]] == false))) {
            highestPheromoneLevel = pheromoneLevels[iPositions[i]];
            highestPheromonePosition = iPositions[i];
        }

    return highestPheromonePosition;
}

double logic::calculate_new_angle(std::vector<double> currentPosition, int iCoordinate, int gridSize)
{
    std::vector<double> finalPosition{logic::convert_from_i_value_to_x_y_coordinates(iCoordinate, gridSize)};

    double adjustedOrientation{atan2(finalPosition[1]-currentPosition[1],finalPosition[0]-currentPosition[0])};
    adjustedOrientation = adjustedOrientation * 57.29575496;

    return adjustedOrientation;
}

bool logic::check_for_intersection(std::vector<double> firstPosition, int firstSize, std::vector<double> secondPosition, int secondSize)
{
    bool intersection{false};

    if((firstPosition[0] + firstSize >= secondPosition[0]) && (firstPosition[1] + firstSize >= secondPosition[1]))
        if((firstPosition[0] <= secondPosition[0] + secondSize) && (firstPosition[1] <= secondPosition[1] + secondSize))
            intersection = true;

    return intersection;
}

bool logic::facing_right(double orientation)
{
    bool facingRight{false};
    if(orientation > 315 || orientation <= 45)
        facingRight = true;
    return facingRight;
}

bool logic::facing_down(double orientation)
{
    bool facing_down{false};
    if (orientation > 45 && orientation <= 135)
        facing_down = true;
    return facing_down;
}

bool logic::facing_left(double orientation)
{
    bool facing_left{false};
    if (orientation >135 && orientation <=225)
        facing_left = true;
    return facing_left;
}

bool logic::facing_up(double orientation)
{
    bool facing_up{false};
    if (orientation >225 && orientation <=315)
        facing_up = true;
    return facing_up;
}

void logic::create_sample_vector(std::vector<int> &iPointsToSample, std::vector<int> &samplePoints)
{
    for(int i = 0; i < samplePoints.size(); i++)
        iPointsToSample.push_back(samplePoints[i]);
    iPointsToSample.erase(iPointsToSample.begin());
}

double logic::convert_to_positive_degree_value(double orientationInDegrees)
{
    while(orientationInDegrees > 360)
        orientationInDegrees = orientationInDegrees - 360;

    while(orientationInDegrees < 0)
        orientationInDegrees = orientationInDegrees + 360;

    return orientationInDegrees;
}
