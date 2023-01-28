
int* get_address_from_2d_array(int* array, unsigned int numberCols, unsigned int r, unsigned int c)
{
    int offset = r*numberCols+c;
    return array+offset;
}

unsigned char get_red_value(int* pixel)
{
    unsigned char* array = reinterpret_cast<unsigned char*>(pixel);
    return array[0];
}

unsigned char get_green_value(int* pixel)
{
    unsigned char* array = reinterpret_cast<unsigned char*>(pixel);
    return array[1];
}

unsigned char get_blue_value(int* pixel)
{
    unsigned char* array = reinterpret_cast<unsigned char*>(pixel);
    return array[2];
}

unsigned char get_alpha_value(int* pixel)
{
    return reinterpret_cast<unsigned char*>(pixel)[3];
}

void set_alpha_value(int* pixel, unsigned char value)
{
    unsigned char* array = reinterpret_cast<unsigned char*>(pixel);
    array[3]=value;
}

void set_rgba_value(int* pixel, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    unsigned char* array = reinterpret_cast<unsigned char*>(pixel);
    array[3]=alpha;
    array[2]=blue;
    array[1]=green;
    array[0]=red;
}

