#ifndef ANT_H
#define ANT_H
#include <vector>

//class pheromone;
class food;

class ant
{
protected:
    std::vector<double> currentPosition{0,0};
    std::vector<double> colony{0,0};
    double orientation{0};
    double variation{0};
    double variationRange{.1};
    bool hasFood = false;
    int gridSize{0};
    int antSize{3};
    int colonySize{0};
    double stepSize{2};
    double sampleSize{25};

public:
    ant();
    void set_starting_point(std::vector<double> startingVector, int gridSize, int colonySize);
    std::vector<double> get_current_position();
    double get_orientation();
    void set_grid_size(int sizeOfGrid);
    void set_has_food_true();
    void set_has_food_false();
    void set_orientation(double angle);
    void set_sample_size(int sampleSizeVal);
    bool check_if_ant_has_food();
    void wander();
    double calculate_distance_from_colony(std::vector<double> colonyLocation);
    void check_boundary();
    void reverse_orientation();
    void assign_orientation();
    void step();
    void generate_random_orientation();
    void sample_in_direction_of_orientation(std::vector<int> &iPointsToSample);
    void reorient_towards_pheromones(std::vector<int> &pheromoneLevels, std::vector<bool> &toHome, food &foodType);
    void reorient_towards_object(int &highestPheromoneLevelPosition, std::vector<int> iPointsToSample, std::vector<double> location, int size);
};

#endif // ANT_H
