#ifndef Layer_hpp
#define Layer_hpp

#include <vector>
#include "Obstacle.hpp"

class Layer
{
public:
    double xlen, ylen;
    std::vector<Obstacle> obs_list;
};

#endif Layer_hpp