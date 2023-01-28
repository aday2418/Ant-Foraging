#include <cmath>
#include "colortools.h"
#include "world.h"

void initialize_color_grid_in_overly_complex_way(int* grid, world& worldType)
{
    std::vector<int> gridVector{worldType.create_a_1d_vector_of_grid_size()};

    int colony = 1;
    int food = 2;
    int pheromoneToHome = 3;
    int pheromoneToFood = 4;
    int antWithoutFood = 5;
    int antWithFood = 6;
    double alpha = 255;
    double pheromoneAlpha = 50;

    for(long unsigned int i = 0; i < gridVector.size(); i++)
    {
        if(gridVector[i] == colony )
            set_rgba_value(grid+i,0,0,255,alpha);

        else if (gridVector[i] == food)
            set_rgba_value(grid+i,0,255,0,alpha);

        else if (gridVector[i] == pheromoneToHome)
            set_rgba_value(grid+i,200,200,0,pheromoneAlpha);

        else if (gridVector[i] == pheromoneToFood)
            set_rgba_value(grid+i,200,20,200,pheromoneAlpha);

        else if (gridVector[i] == antWithoutFood)
            set_rgba_value(grid+i,255,0,0,alpha);

        else if (gridVector[i] == antWithFood)
            set_rgba_value(grid+i,255,51,255,alpha);
        else
            set_rgba_value(grid+i,255,255,255,alpha);
    }
}
