#ifndef COLORGRID_H
#define COLORGRID_H
#include <vector>
#include "world.h"

class ColorGrid
{
public:
    ColorGrid(unsigned int width, unsigned int height);
    void update_values(world& worldType);
    const unsigned char* get_data()const;
    unsigned int get_width();
    unsigned int get_height();
protected:
    unsigned int width{0};
    unsigned int height{0};
    std::vector<int> grid;
    std::vector<char> direction;
};

#endif // COLORGRID_H
