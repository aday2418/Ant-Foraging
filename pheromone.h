#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>

class pheromone
{
protected:
    int level{0};
    int location{0};
    bool toHome{true};
    int incrementLevel{300};

public:
    pheromone() = default;
    void set_location(int location);
    void increment_pheremone_level(int distanceFromColony);
    void decrement_pheromone_level();
    void set_to_home();
    void set_to_food();
    void clear();
    bool get_if_pheromone_is_to_home();
    int get_level();

};

#endif // PHEROMONE_H
