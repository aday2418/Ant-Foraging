#include "colorgrid.h"
#include "colorgridutils.h"
#include <iostream>
#include "world.h"

ColorGrid::ColorGrid(unsigned int w, unsigned int h):width{w}, height{h}
{
    grid.resize(width*height);
    direction.resize(width*height);
}

void ColorGrid::update_values(world& worldType)
{
    initialize_color_grid_in_overly_complex_way(grid.data(), worldType);
}

const unsigned char* ColorGrid::get_data() const
{
    return reinterpret_cast<const unsigned char*>(grid.data());
}

unsigned int ColorGrid::get_width()
{
    return width;
}

unsigned int ColorGrid::get_height()
{
    return height;
}
