#include "ViewTexture.hpp"

#include <cstdio>
#include <cmath>

#include "ysglfontdata.h"

double ViewTexture::W2CX(double x)
{
    return x * window_x_len / double(world.layer_x_len);
}

double ViewTexture::W2CY(double y)
{
    double fy = world.layer_y_len - (y - world.current_layer * world.layer_y_len);
    return fy * window_y_len / world.layer_y_len;
}

ViewTexture::ViewTexture()
{
}

ViewTexture::~ViewTexture()
{
    Cleanup();
}

void ViewTexture::Cleanup()
{
    if (nullptr == texData)
    {
        delete texData;
    }
}

void ViewTexture::InitTexture()
{
    int rgba_idx = 0;
    printf("texdata size: %d\n", texData->size);
    for (int i = 0; i < texData->size; ++i)
    {
        rgba_idx = i * 4;
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(texData->rgba[rgba_idx],
                  texData->rgba[rgba_idx + 1],
                  texData->rgba[rgba_idx + 2],
                  texData->rgba[rgba_idx + 3]);
        glGenTextures(1, &texData->texIds[i]);
        glBindTexture(GL_TEXTURE_2D, texData->texIds[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     texData->decoders[i].wid,
                     texData->decoders[i].hei,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     texData->decoders[i].rgba);
    }

    glEnable(GL_TEXTURE_2D); // Begin using texture mapping
}

void ViewTexture::DrawTransparent(double x[], double y[], double rgba[])
{
    glBegin(GL_QUADS);
    glColor4ub(128, 128, 128, 255);
    glVertex2d(x[0], y[0]);
    glVertex2d(x[1], y[1]);
    glVertex2d(x[2], y[2]);
    glVertex2d(x[3], y[3]);
    glEnd();
//    glDisable(GL_BLEND);
}

void ViewTexture::DrawQuadTex(double x[], double y[], int texId, double rgba[])
{
    glBindTexture(GL_TEXTURE_2D, texData->texIds[0]);
    glBegin(GL_QUADS);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glTexCoord2d(0.0, 0.0); // top part
    glVertex2d(x[0], y[0]); // w2cx, w2cy+y-1
    glTexCoord2d(1.0, 0.0);
    glVertex2d(x[1], y[1]); // w2cx+x, w2cy+y-1
    glTexCoord2d(1.0, 1.0);
    glVertex2d(x[2], y[2]); // w2cx+x, w2cy+y
    glTexCoord2d(0.0, 1.0);
    glVertex2d(x[3], y[3]); // w2cx, w2cy+y
    glEnd();
}

void ViewTexture::DrawBackground(int texId)
{
    glBindTexture(GL_TEXTURE_2D, texData->texIds[1]);
    glBegin(GL_QUADS);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(0, 0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(window_x_len, 0); // window size
    glTexCoord2d(1.0, 1.0);
    glVertex2d(window_x_len, window_y_len); // window size
    glTexCoord2d(0.0, 1.0);
    glVertex2d(0, window_y_len); // window size
    glEnd();
}

void ViewTexture::DrawObstacleOne(Obstacle &obs, int texId)
{
    double x_in[4] = {
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + 0.5)};
    double y_in[4] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_left[4] = {
        W2CX(obs.GetX()),
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX())};
    double y_left[4] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_right[4] = {
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5)};
    double y_right[4] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_top[4] = {
        W2CX(obs.GetX()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX())};
    double y_top[4] = {
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen()),
        W2CY(obs.GetY() + obs.GetYlen())};
    double rgba[4] = {1.0, 1.0, 1.0, 1.0};
    DrawQuadTex(x_left, y_left, 0, rgba);
    DrawQuadTex(x_right, y_right, 0, rgba);
    DrawQuadTex(x_top, y_top, 0, rgba);
    DrawTransparent(x_in, y_in, rgba);
}

void ViewTexture::DrawObstacles(void)
{
    for (Obstacle obs : world.layer_list.at(world.current_layer).obs_list)
    {
        DrawObstacleOne(obs, 0);
    }
}

void ViewTexture::DrawHero()
{
    // draw circle-bounded banana
    // Draw externally and load from PNG (6 states) OR draw by OpenGL (texture) (quite complicated)
}

void ViewTexture::DrawForeground()
{
    glBindTexture(GL_TEXTURE_2D, texData->texIds[2]);
    glBegin(GL_QUADS);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(0, 0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(window_x_len, 0); // window size
    glTexCoord2d(1.0, 1.0);
    glVertex2d(window_x_len, window_y_len); // window size
    glTexCoord2d(0.0, 1.0);
    glVertex2d(0, window_y_len); // window size
    glEnd();
}

void ViewTexture::DrawUI()
{
    // Top layer texts that keep showing all the time in game
    // Introduction / Conclusion can be done later
    glColor3ub(0, 0, 0);
    glRasterPos2d(5, 25); // TBD
    char buffer[30];
    std::sprintf(buffer, "Current Layer: %d", world.current_layer);
    YsGlDrawFontBitmap16x20(buffer);
}

void ViewTexture::Render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//    InitTexture();
    DrawBackground(0);
    DrawObstacles();
    //    DrawHero();
    DrawForeground();
//    DrawUI();
    glDisable(GL_BLEND);
}

void ViewTexture::Next(double time_interval, SpaceEvent se, HeroMoveDir dir, double intensity)
{
    if (spacePressed == se && world.hero.heroState == onLand)
    {
        world.hero.heroState = charging;
    }
    world.Next(time_interval, dir, intensity);
}
