#include "World.hpp"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <cmath>
#include <string>

const double EM_PI = 3.1415926535;

class View4Test
{
public:
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
    // manipulating world
    void next(double time_interval); //?
    // init
    void Init(World w);

protected:
    World world;
};