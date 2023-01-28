#include "ant.h"
#include <iostream>
#include <cmath>
#include "logic.h"
#include "food.h"

ant::ant()
{
    generate_random_orientation();
}

void ant::set_starting_point(std::vector<double> startingVector, int gridSizeVal, int colonySizeVal)
{
    gridSize = gridSizeVal;
    colonySize = colonySizeVal;

    colony[0] = startingVector[0] - colonySize/2; //Check this before submitting
    colony[1] = startingVector[1] - colonySize/2;

    generate_random_orientation();

    currentPosition[0] = colony[0] + colonySize;
    currentPosition[1] = colony[1] + colonySize;
}

std::vector<double> ant::get_current_position()
{
    return currentPosition;
}

void ant::set_has_food_true()
{
    hasFood = true;
    reverse_orientation();
}

void ant::set_has_food_false()
{
    hasFood = false;
    reverse_orientation();
}

void ant::set_orientation(double angle)
{
    orientation = angle * 0.0174533;
}

void ant::set_sample_size(int sampleSizeVal)
{
    sampleSize = sampleSizeVal;
}

double ant::get_orientation()
{
    double orientationInDegrees{orientation * 57.29575496};
    orientationInDegrees = logic::convert_to_positive_degree_value(orientationInDegrees);

    return orientationInDegrees;
}

bool ant::check_if_ant_has_food()
{
    if (hasFood == true)
        return true;
    else
        return false;
}

void ant::wander()
{
    assign_orientation();
    step();
    check_boundary();
}

void ant::assign_orientation()
{
    variation = logic::generate_random_double(-variationRange,variationRange);
    orientation += variation;
}

void ant::step()
{
    currentPosition[0] += stepSize*cos(orientation);
    currentPosition[1] += stepSize*sin(orientation);
}

void ant::generate_random_orientation() //Add a test for this function
{
    orientation = logic::generate_random_double(0,360);
    orientation = orientation * 0.0174533;
}

void ant::check_boundary()
{
    if(currentPosition[0] < antSize || currentPosition[0] > gridSize-antSize || currentPosition[1] < antSize || currentPosition[1] > gridSize-antSize)
        reverse_orientation();
}

double ant::calculate_distance_from_colony(std::vector<double> colonyLocation)
{
    double distance = ((colonyLocation[0] - currentPosition[0]) * (colonyLocation[0] - currentPosition[0]));
    distance += ((colonyLocation[1] - currentPosition[1]) * (colonyLocation[1] - currentPosition[1]));
    distance = sqrt(distance);

    return distance;
}

void ant::reverse_orientation()
{
    orientation += 3.14;
}

void ant::reorient_towards_pheromones(std::vector<int> &pheromoneLevels, std::vector<bool> &toHome, food &foodType)
{
    int highestPheromoneLevelPosition{0};
    std::vector<int> iPointsToSample{0};

    sample_in_direction_of_orientation(iPointsToSample);
    highestPheromoneLevelPosition = logic::get_position_of_highest_pheromone_level(hasFood, iPointsToSample, pheromoneLevels, toHome);

    if(hasFood == true)
        reorient_towards_object(highestPheromoneLevelPosition,iPointsToSample,colony,colonySize);

    if(hasFood == false)
    {
        std::vector<double> foodLocation{foodType.get_food_location()};
        foodLocation[0] += -foodType.get_size_of_food()/2;
        foodLocation[1] += -foodType.get_size_of_food()/2;
        reorient_towards_object(highestPheromoneLevelPosition,iPointsToSample,foodLocation,foodType.get_size_of_food());
    }

    if(highestPheromoneLevelPosition != 0)
    {
        double newOrientation{logic::calculate_new_angle(get_current_position(), highestPheromoneLevelPosition, gridSize)};
        set_orientation(newOrientation);
    }
}

void ant::reorient_towards_object(int &highestPheromoneLevelPosition, std::vector<int> iPointsToSample, std::vector<double> location, int size)
{
    for(int i = 0; i < iPointsToSample.size(); i++)
    {
        std::vector<double> xyCoord{logic::convert_from_i_value_to_x_y_coordinates(iPointsToSample[i],gridSize)};
        if(logic::check_for_intersection(xyCoord, 1, location, size))
            highestPheromoneLevelPosition = iPointsToSample[i];
    }
}

void ant::sample_in_direction_of_orientation(std::vector<int> &iPointsToSample)
{
    double orientation = get_orientation();

    if (logic::facing_right(orientation))
    {
        std::vector<int> samplePoints{logic::sample_right(sampleSize, currentPosition[0], currentPosition[1], gridSize)};
        logic::create_sample_vector(iPointsToSample,samplePoints);
    }
    else if (logic::facing_down(orientation))
    {
        std::vector<int> samplePoints{logic::sample_down(sampleSize, currentPosition[0], currentPosition[1], gridSize)};
        logic::create_sample_vector(iPointsToSample,samplePoints);
    }
    else if (logic::facing_left(orientation))
    {
        std::vector<int> samplePoints{logic::sample_left(sampleSize, currentPosition[0], currentPosition[1], gridSize)};
        logic::create_sample_vector(iPointsToSample,samplePoints);
    }
    else if (logic::facing_up(orientation))
    {
        std::vector<int> samplePoints{logic::sample_up(sampleSize, currentPosition[0], currentPosition[1], gridSize)};
        logic::create_sample_vector(iPointsToSample,samplePoints);
    }
}
