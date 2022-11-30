#ifndef View_hpp
#define View_hpp

#include "World.hpp"
#include "Controller.hpp"

#ifndef CONST_EM_PI
#define CONST_EM_PI
const double EM_PI = 3.1415926535;
#endif

class View4Test
{
public:
    View4Test();
    ~View4Test();

    int window_x_len, window_y_len;

    void Cleanup();
    // world to canvas
    double W2CX(double x);
    double W2CY(double y);
    // rendering function
    void DrawBackground(void);
    void DrawObstacleOne(Obstacle &obs);
    void DrawObstacles(void);
    void DrawHero(void);
    void DrawUI(void);
    void Render(void);
    // manipulating world
    void Next(double time_interval, SpaceEvent s, HeroMoveDir dir, double intensity);
    World world;
};
#endif /* View_hpp */
