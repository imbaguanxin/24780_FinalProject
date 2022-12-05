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
    World world;
    int windowXLen, windowYLen;
    View4Test();
    ~View4Test();

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
};
#endif /* View_hpp */
