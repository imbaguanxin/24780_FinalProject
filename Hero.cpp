#include "Hero.hpp"

Hero::Hero(void)
{
    x = 20.0;
    y = 20.0;
    vx = 0.0;
    vy = 0.0;
    ay = 9.8;
    radius = 0.0;
    heroState = onLand;
    heroDir = stand;
}

Hero::~Hero(void)
{
}
