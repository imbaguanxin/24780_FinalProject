#include "View.hpp"

// assume each frame is 30 * 30m
// project to a 600 * 600 pixel
double View4Test::W2CX(double x)
{
    return x * 20;
}

double View4Test::W2CY(double y)
{
    double frame_size = 600;
    double frame_offset = world.current_layer * frame_size;
    return frame_size - (y - frame_offset);
}

void View4Test::View4Test()
{
}

void View4Test::~View4Test()
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
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d(W2CX(obs.GetX()), W2CY(obs.GetY()));
    glVertex2d(W2CX(obs.GetX() + obs.GetXlen()), W2CY(obs.GetY()));
    glVertex2d(W2CX(obs.GetX() + obs.GetXlen()), W2CY(obs.GetY() + obs.GetYlen()));
    glVertex2d(W2CX(obs.GetX()), W2CY(obs.GetY() + obs.GetYlen()));
    glEnd();
}

void View4Test::DrawObstacles()
{
    // Left, top and right edge: call render(), bind with texture (https://learnopengl.com/Getting-started/Textures)
    // Middle part: transparent block (alpha blending, lecture 6)

    for (Obstacle obs : world.layer_list.at(world.current_layer).obs_list)
    {

        DrawObstacleOne(obs);
    }
}

void View4Test::DrawHero()
{
    // draw circle-bounded banana
    // Draw externally and load from PNG (6 states) OR draw by OpenGL (texture) (quite complicated)
    const int segment = 64;
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
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

    glRasterPos2i(600, 600); // TBD
    std::String = std::format("Current Layer: %d", world.current_layer);
    YsGlDrawFontBitmap8x8(str);
}

void View4Test::Render()
{
    DrawBackground();
    DrawObstacles();
    DrawHero();
    DrawUI();
}

void View4Test::next(double time_interval)
{
}

void View4Test::Init(World w)
{
}