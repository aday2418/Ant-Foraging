#ifndef COLORTOOLS_H
#define COLORTOOLS_H
#include <array>

int* get_address_from_2d_array(int* array, unsigned int numberCols, unsigned int r, unsigned int c);

unsigned char get_alpha_value(int* pixel);
unsigned char get_red_value(int* pixel);
unsigned char get_green_value(int* pixel);
unsigned char get_blue_value(int* pixel);

void set_alpha_value(int* pixel, unsigned char value);
void set_rgba_value(int* pixel, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

#endif // COLORTOOLS_HPP
