#ifndef LOGIC_H
#define LOGIC_H
#include <vector>

class world;

namespace logic
{
double generate_random_double(double minValue, double maxValue);
double calculate_new_angle(std::vector<double> currentPosition, int iCoordinate, int gridSize);
int convert_from_x_y_double_coordinates_to_i_value(std::vector<double> xyCoordinates, int gridSize);
int get_position_of_highest_pheromone_level(bool antHasFood, std::vector<int> &iPositions, std::vector<int> &pheromoneLevels, std::vector<bool> &toHome);
std::vector<double> convert_from_i_value_to_x_y_coordinates(int iVal, int gridSize);
std::vector<int> create_vector_of_all_i_values_to_paint(int iStartingValue, int paintSize, int gridSize);
std::vector<int> sample_right(int sampleSize, double xPosition, double yPosition, int gridSize);
std::vector<int> sample_left(int sampleSize, double xPosition, double yPosition, int gridSize);
std::vector<int> sample_down(int sampleSize, double xPosition, double yPosition, int gridSize);
std::vector<int> sample_up(int sampleSize, double xPosition, double yPosition, int gridSize);
bool facing_up(double orientation);
bool facing_right(double orientation);
bool facing_down(double orientation);
bool facing_left(double orientation);
bool check_for_intersection(std::vector<double> firstPosition, int firstSize, std::vector<double> secondPosition, int secondSize);
void create_sample_vector(std::vector<int> &iPointsToSample, std::vector<int> &samplePoints);
double convert_to_positive_degree_value(double originalVal);
};

#endif // LOGIC_H
