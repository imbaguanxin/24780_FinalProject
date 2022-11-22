#ifndef Hero_hpp
#define Hero_hpp

enum HeroState
{
    onLand,
    onAir,
    charging,
};

enum HeroMoveDir
{
    moveLeft,
    moveRight
};

class Hero
{
public:
    double x, y;
    double vx, vy;
    double radius;
    HeroState heroState;
    HeroMoveDir heroDir;
};

#endif