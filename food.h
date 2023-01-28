#ifndef FOOD_H
#define FOOD_H
#include <vector>

class food
{
protected:
    int startingFoodSize{100};
    int foodSize{startingFoodSize};
    int foodSmallestSize{10};
    int gridSize{0};
    std::vector<double> foodLocation{0,0};

public:
    food() = default;
    std::vector<double> get_food_location();
    int get_size_of_food();
    void food_eaten();
    void reset_food();
    void generate_new_food_location(int gridSize);
};

#endif // FOOD_H
