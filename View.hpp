#include "World.hpp"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <cmath>
#include <string>

const double Pi = 3.1415926535;

class View
{
public:
    View();
    ~View();
    void Cleanup();
    void drawBackground(void);
    void drawObstacle(void);
    void drawHero(void);
    void drawUI(void);
    void render(void);
    void next(double time_interval); //?

protected:
    World world;
};

void View::View() {
    
}

void View::~View() {
    Cleanup();
}

void View::Cleanup() {

}

void View::drawBackground() {
    // PNG (yspng) OR draw by OpenGL (shapes and fill with color) (2D first, 3D maybe later)
    // Bottom animation at the start line
}

void View::drawObstacle() {
    // Left, top and right edge: call render(), bind with texture (https://learnopengl.com/Getting-started/Textures)
    // Middle part: transparent block (alpha blending, lecture 6)

    for (auto obs : world.layer_list.at(world.current_layer).obs_list) {
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2d(obs.GetX() - obs.GetWidth / 2, obs.GetY() - obs.GetHeight() / 2);
        glVertex2d(obs.GetX() + obs.GetWidth / 2, obs.GetY() - obs.GetHeight() / 2);
        glVertex2d(obs.GetX() + obs.GetWidth / 2, obs.GetY() + obs.GetHeight() / 2);
        glVertex2d(obs.GetX() - obs.GetWidth / 2, obs.GetY() + obs.GetHeight() / 2);
        glEnd();

        render();
    }
}

void View::drawHero() {
    // draw circle-bounded banana
    // Draw externally and load from PNG (6 states) OR draw by OpenGL (texture) (quite complicated)

    glBegin(GL_POLYGON);
    for (int i = 0; i < 64; ++i)
    {
        double a = Pi * (double)i / 32;
        double dx = cos(a) * world.hero.radius;
        double dy = sin(a) * world.hero.radius;
        glVertex2d(world.hero.x + dx, world.hero.y + dy);
    }
    glEnd();
}

void View::drawUI() {
    // Top layer texts that keep showing all the time in game
    // Introduction / Conclusion can be done later

    glRasterPos2i(400,700); // TBD
    std::string str = "Current Layer: ";
    str += std::to_string(world.current_layer);
    //str.append({ world.current_layer });
    YsGlDrawFontBitmap24x40(str);
}

void View::render() {

}

void View::next(double time_interval) {

}