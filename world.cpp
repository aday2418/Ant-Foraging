#include "world.h"
#include "logic.h"
#include <iostream>
#include <cmath>

world::world()
{
    reset();
}

int world::get_grid_size()
{
    return gridSize;
}

int world::get_colony_size()
{
    return colonySize;
}

int world::get_food_size()
{
    return foodType.get_size_of_food();
}

int world::get_ant_size()
{
    return antSize;
}

void world::reset()
{
    generate_colony();
    generate_food();
    generate_ants();
    generate_pheromones();
}

void world::generate_colony()
{
    colony[0] = logic::generate_random_double(0,gridSize-get_colony_size());
    colony[1] = logic::generate_random_double(0,gridSize-get_colony_size());
}

void world::generate_food()
{
    do foodType.generate_new_food_location(gridSize);
    while(logic::check_for_intersection(foodType.get_food_location(),foodType.get_size_of_food(),colony,colonySize));
}

void world::generate_ants()
{
    antType.resize(numAnts);

    for(int i = 0; i < antType.size(); i++)
        antType[i].set_starting_point(get_colony(),gridSize, colonySize);
}

void world::generate_pheromones()
{
    pheromoneType.resize(gridSize*gridSize);

    for(int i = 0; i < pheromoneType.size(); i++)
        pheromoneType[i].set_location(i);
}

std::vector<double> world::get_colony()
{
    return colony;
}

std::vector<double> world::get_food()
{
    return foodType.get_food_location();
}

std::vector<int> world::get_vector_of_pheromone_levels()
{
    std::vector<int> pheromoneLevels(pheromoneType.size(),0);

    for(int i = 0; i < pheromoneType.size(); i++)
        pheromoneLevels[i] = pheromoneType[i].get_level();

    return pheromoneLevels;
}

std::vector<bool> world::get_vector_of_if_pheromones_are_to_home()
{
    std::vector<bool> pheromoneToHome(pheromoneType.size(),true);

    for(int i = 0; i < pheromoneType.size(); i++)
        pheromoneToHome[i] = pheromoneType[i].get_if_pheromone_is_to_home();

    return pheromoneToHome;
}

void world::update_values()
{
    update_ant_positions();
    update_food();
    update_pheromone_levels();
}

void world::update_ant_positions()
{
    std::vector<int> currentPheromoneLevels{get_vector_of_pheromone_levels()};
    std::vector<bool> toHome{get_vector_of_if_pheromones_are_to_home()};

    for(int i = 0; i < antType.size(); i++)
    {
        antType[i].reorient_towards_pheromones(currentPheromoneLevels, toHome, foodType);
        antType[i].wander();
    }
}

void world::update_food()
{
    for(int i = 0; i < antType.size(); i++)
    {
        std::vector<double> antPosition{antType[i].get_current_position()};

        if(!antType[i].check_if_ant_has_food())
            if(logic::check_for_intersection(antPosition,antSize,foodType.get_food_location(),foodType.get_size_of_food()))
            {
                foodType.food_eaten();
                antType[i].set_has_food_true();
            }

        if(antType[i].check_if_ant_has_food())
            if(logic::check_for_intersection(antPosition,antSize,colony,colonySize))
                antType[i].set_has_food_false();
    }
}

void world::update_pheromone_levels()
{

    scatter_pheromones();
    diminish_pheromones();
}

void world::scatter_pheromones()
{
    for(int i = 0; i < antType.size(); i++)
    {
        int antPosition{logic::convert_from_x_y_double_coordinates_to_i_value(antType[i].get_current_position(),gridSize)};
        for(int j = -pheromoneScatterSize/2; j < pheromoneScatterSize/2; j++)
        {
            pheromoneType[antPosition + j].increment_pheremone_level(antType[i].calculate_distance_from_colony(colony));

            if(antType[i].check_if_ant_has_food() == true)
                pheromoneType[antPosition + j].set_to_food();
            else
                pheromoneType[antPosition + j].set_to_home();
        }
    }
}

void world::diminish_pheromones()
{
    for(int i = 0; i < pheromoneType.size(); i++)
        pheromoneType[i].decrement_pheromone_level();
}

std::vector<int> world::create_a_1d_vector_of_grid_size()
{
    std::vector<int> gridPoints(gridSize*gridSize,0);

    add_pheromones_to_grid(gridPoints);
    add_colony_to_grid(gridPoints);
    add_food_to_grid(gridPoints);
    add_ants_to_grid(gridPoints);

    return gridPoints;
}

void world::add_pheromones_to_grid(std::vector<int> &gridPoints)
{
    std::vector<int> pheromonePoints{get_vector_of_pheromone_levels()};
    std::vector<bool> pheromoneToHome{get_vector_of_if_pheromones_are_to_home()};

    for(int i = 0; i < pheromonePoints.size(); i++)
    {
        if(pheromonePoints[i] > 0 && pheromoneToHome[i] == true)
            gridPoints[i] = 3;

        if(pheromonePoints[i] > 0 && pheromoneToHome[i] == false)
            gridPoints[i] = 4;
    }
}

void world::add_colony_to_grid(std::vector<int> &gridPoints)
{
    int colonyStartingPoint = logic::convert_from_x_y_double_coordinates_to_i_value(get_colony(),get_grid_size());
    std::vector<int> colonyPoints{logic::create_vector_of_all_i_values_to_paint(colonyStartingPoint,get_colony_size(),get_grid_size())};
    for(int i = 0; i < colonyPoints.size(); i++)
    {
        int j = colonyPoints.at(i);
        gridPoints[j] = 1;
    }
}

void world::add_food_to_grid(std::vector<int> &gridPoints)
{
    int foodStartingPoint = logic::convert_from_x_y_double_coordinates_to_i_value(get_food(),get_grid_size());
    std::vector<int> foodPoints{logic::create_vector_of_all_i_values_to_paint(foodStartingPoint,get_food_size(),get_grid_size())};

    for(int i = 0; i < foodPoints.size(); i++)
    {
        int j = foodPoints.at(i);
        gridPoints[j] = 2;
    }
}

void world::add_ants_to_grid(std::vector<int> &gridPoints)
{
    for(int i = 0; i < numAnts; i++)
    {
        std::vector<double> antStartingVector{antType[i].get_current_position()};
        int antStartingPoint = logic::convert_from_x_y_double_coordinates_to_i_value(antStartingVector,get_grid_size());
        std::vector<int> antPoints{logic::create_vector_of_all_i_values_to_paint(antStartingPoint,get_ant_size(),get_grid_size())};

        for(int k = 0; k < antPoints.size(); k++)
        {
            int j = antPoints.at(k);
            if(antType[i].check_if_ant_has_food() == 0)
                gridPoints[j] = 5;
            else
                gridPoints[j] = 6;
        }
    }
}






