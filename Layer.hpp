#ifndef STD_VECTOR_IS_INCLUDED
#include <vector>
#define STD_VECTOR_IS_INCLUDED
#endif

#ifndef OBSTACLE_IS_INCLUDED
#include "Obstacle.hpp"
#define OBSTACLE_IS_INCLUDED
#endif

class Layer
{
public:
    double xlen, ylen;
    std::vector<Obstacle> obs_list;
};