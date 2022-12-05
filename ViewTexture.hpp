#ifndef ViewTexture_hpp
#define ViewTexture_hpp

#include "fssimplewindow.h"
#include "yspng.h"
#include "World.hpp"
#include "Controller.hpp"

#ifndef CONST_EM_PI
#define CONST_EM_PI
const double EM_PI = 3.1415926535;
#endif

class TextureData
{
public:
    YsRawPngDecoder *decoders = nullptr;
    GLuint *texIds = nullptr;
    float *rgba = nullptr;
    int size = 0;

    TextureData(int length)
    {
        if (length <= 0)
        {
            size = 0;
        }
        else
        {
            size = length;
        }
        decoders = new YsRawPngDecoder[size];
        texIds = new GLuint[size];
        rgba = new float[4 * size];
    }

    ~TextureData()
    {
        if (nullptr == decoders)
        {
            delete[] decoders;
        }
        if (nullptr == texIds)
        {
            delete[] texIds;
        }
        if (nullptr == rgba)
        {
            delete[] rgba;
        }
    }

    void setRGBA(float c[])
    {
        for (int i = 0; i < size * 4; ++i)
        {
            rgba[i] = c[i];
        }
    }
};

class ViewTexture
{
public:
    World world;
    int window_x_len, window_y_len;
    TextureData *texData = nullptr;

    ViewTexture();
    ~ViewTexture();
    void Cleanup();
    // world to canvas
    double W2CX(double x);
    double W2CY(double y);
    // rendering function
    void DrawBackground(int texId);
    void DrawObstacleOne(Obstacle &obs, int texId);
    void DrawObstacles(void);
    void DrawHero(double intensity);
    void DrawUI(void);
    void DrawForeground(void);
    void Render(double intensity);
    // manipulating world
    void Next(double time_interval, SpaceEvent s, HeroMoveDir dir, double intensity);
    void InitTexture();

protected:
    void DrawTransparent(double x[], double y[], double rgba[]);
    void DrawQuadTex(double x[], double y[], int texId, double rgba[]);
};

#endif /* ViewTexture_hpp */
