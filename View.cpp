#include <cstdio>
#include <cmath>

#include "View.hpp"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

double View4Test::W2CX(double x)
{
    return x * windowXLen / double(world.layerXLen);
}

double View4Test::W2CY(double y)
{
    double fy = world.layerYLen - (y - world.currentLayer * world.layerYLen);
    return fy * windowYLen / world.layerYLen;
}

View4Test::View4Test()
{
}

View4Test::~View4Test()
{
    Cleanup();
}

void View4Test::Cleanup()
{
}

void View4Test::DrawBackground()
{
    // PNG (yspng) OR draw by OpenGL (shapes and fill with color) (2D first, 3D maybe later)
    // Bottom animation at the start line
}

void View4Test::DrawObstacleOne(Obstacle &obs)
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2d(W2CX(obs.GetX()), W2CY(obs.GetY()));
    glVertex2d(W2CX(obs.GetX() + obs.GetXlen()), W2CY(obs.GetY()));
    glVertex2d(W2CX(obs.GetX() + obs.GetXlen()), W2CY(obs.GetY() + obs.GetYlen()));
    glVertex2d(W2CX(obs.GetX()), W2CY(obs.GetY() + obs.GetYlen()));
    glEnd();
}

void View4Test::DrawObstacles()
{
    if (world.CheckWin()){
        return;
    }
    for (Obstacle obs : world.layerList.at(world.currentLayer).obsList)
    {
        DrawObstacleOne(obs);
    }
}

void View4Test::DrawHero()
{
    // draw circle-bounded banana
    // Draw externally and load from PNG (6 states) OR draw by OpenGL (texture) (quite complicated)
    const int segment = 64;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 0);
    for (int i = 0; i < segment; ++i)
    {
        double theta = 2 * EM_PI * double(i) / segment;
        double x = world.hero.x + cos(theta) * world.hero.radius;
        double y = world.hero.y + sin(theta) * world.hero.radius;
        glVertex2d(W2CX(x), W2CY(y));
    }
    glEnd();
}

void View4Test::DrawUI()
{
    // Top layer texts that keep showing all the time in game
    // Introduction / Conclusion can be done later
    glColor3ub(0, 0, 0);
    glRasterPos2d(5, 25); // TBD
    char buffer[30];
    std::sprintf(buffer, "Current Layer: %d", world.currentLayer);
    YsGlDrawFontBitmap16x20(buffer);
}

void View4Test::Render()
{
    DrawBackground();
    DrawObstacles();
    DrawHero();
    DrawUI();
}
