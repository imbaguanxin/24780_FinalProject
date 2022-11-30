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
    stand,
    moveLeft,
    moveRight,
};

class Hero
{
public:
    double x, y;
    double vx, vy;
    double ay;
    double radius;
    const double jumpSpeed = 10;
    HeroState heroState;
    HeroMoveDir heroDir;

    Hero(void);
    ~Hero(void);
};

#endif
