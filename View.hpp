#ifndef View_hpp
#define View_hpp

#include "World.hpp"

const double EM_PI = 3.1415926535;

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
    void Next(double time_interval); //?
    // init
    void Init(World &w);
    World world;
};
#endif /* View_hpp */
