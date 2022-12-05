#ifndef Layer_hpp
#define Layer_hpp

#include <vector>
#include "Obstacle.hpp"

class Layer
{
public:
    double xlen, ylen;
    std::vector<Obstacle> obsList;
};

#endif Layer_hpp
