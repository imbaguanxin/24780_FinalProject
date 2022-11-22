#ifndef STD_VECTOR_IS_INCLUDED
#include <vector>
#define STD_VECTOR_IS_INCLUDED
#endif

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
};

class Obstacle
{
protected:
    // lower left position
    double blx, bly;
    double xlen, ylen;

public:
    Obstacle();
    int GetX(void);
    int GetY(void);
    int GetXlen(void);
    int GetYlen(void);
    void Init(double X, double Y, double Width, double Height);
};

class Layer
{
public:
    double xlen, ylen;
    std::vector<Obstacle> obs_list;
};

class World
{
public:
    Hero hero;
    std::vector<Layer> layer_list;
    int current_layer;

    void MoveHero(HeroMoveDir dir);
    void JumpHero(double instensity, HeroMoveDir dir);
    void Next(double time_interval);

protected:
    // obstcle* binded_obstacle;
    // physical simulation
    void CheckHit(void);
    void RenewLayer(void);
    // more functions here
    // TODO:
};
