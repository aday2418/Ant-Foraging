#include "pheromone.h"
#include <iostream>

void pheromone::set_location(int pheromoneLocation)
{
    location = pheromoneLocation;
    level = 0;
}

void pheromone::increment_pheremone_level(int distanceFromColony)
{
    level = level + incrementLevel - distanceFromColony*.5;
}

void pheromone::decrement_pheromone_level()
{
    if(level > 0)
        level--;
    else
        level = 0;
}

void pheromone::set_to_home()
{
    toHome = true;
}

void pheromone::set_to_food()
{
    toHome = false;
}

void pheromone::clear()
{
    level = 0;
}

bool pheromone::get_if_pheromone_is_to_home()
{
    return toHome;
}

int pheromone::get_level()
{
    return level;
}

