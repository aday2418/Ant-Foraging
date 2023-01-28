#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "food.h"
#include "ant.h"
#include "pheromone.h"

class world
{
protected:
    int gridSize{400};
    int colonySize{100};
    const int numAnts{50};
    int antSize{2};
    int pheromoneScatterSize{2};
    std::vector<double> colony{0,0};
    food foodType;
    std::vector<ant> antType;
    std::vector<pheromone> pheromoneType;
public:
    world();
    int get_grid_size();
    int get_colony_size();
    int get_food_size();
    int get_ant_size();

    void reset();
    void generate_colony();
    void generate_food();
    void generate_ants();
    void generate_pheromones();

    std::vector<double> get_colony();
    std::vector<double> get_food();
    std::vector<int> get_vector_of_pheromone_levels();
    std::vector<bool> get_vector_of_if_pheromones_are_to_home();

    void update_values();
    void update_ant_positions();
    void update_food();
    void update_pheromone_levels();
    void scatter_pheromones();
    void diminish_pheromones();

    std::vector<int> create_a_1d_vector_of_grid_size();
    void add_pheromones_to_grid(std::vector<int> &gridPoints);
    void add_colony_to_grid(std::vector<int> &gridPoints);
    void add_food_to_grid(std::vector<int> &gridPoints);
    void add_ants_to_grid(std::vector<int> &gridPoints);
};

#endif // WORLD_H
