#include "ViewTexture.hpp"

#include <cstdio>
#include <cmath>

#include "ysglfontdata.h"

double ViewTexture::W2CX(double x)
{
    return x * windowXLen / double(world.layerXLen);
}

double ViewTexture::W2CY(double y)
{
    double fy = world.layerYLen - (y - world.currentLayer * world.layerYLen);
    return fy * windowYLen / world.layerYLen;
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
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
    glVertex2d(x[0], y[0]);
    glVertex2d(x[1], y[1]);
    glVertex2d(x[2], y[2]);
    glVertex2d(x[3], y[3]);
    glEnd();
}

void ViewTexture::DrawQuadTex(double x[], double y[], int texId, double rgba[])
{
    glBindTexture(GL_TEXTURE_2D, texData->texIds[texId]);
    glBegin(GL_QUADS);
    glColor4d(rgba[0], rgba[1], rgba[2], rgba[3]);
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
    double x[] = {0.0, double(windowXLen), double(windowXLen), 0};
    double y[] = {0.0, 0.0, double(windowYLen), double(windowYLen)};
    double rgba[] = {1.0, 1.0, 1.0, 1.0};
    DrawQuadTex(x, y, texId, rgba);
}

void ViewTexture::DrawObstacleOne(Obstacle &obs, int texId)
{
    double x_in[4] = {
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + 0.5)};
    double y_in[] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_left[] = {
        W2CX(obs.GetX()),
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX() + 0.5),
        W2CX(obs.GetX())};
    double y_left[] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_right[] = {
        W2CX(obs.GetX() + obs.GetXlen() - 0.5),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen() - 0.5)};
    double y_right[] = {
        W2CY(obs.GetY()),
        W2CY(obs.GetY()),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5)};
    double x_top[] = {
        W2CX(obs.GetX()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX() + obs.GetXlen()),
        W2CX(obs.GetX())};
    double y_top[] = {
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen() - 0.5),
        W2CY(obs.GetY() + obs.GetYlen()),
        W2CY(obs.GetY() + obs.GetYlen())};
    double rgba[] = {1.0, 1.0, 1.0, 1.0};
    DrawQuadTex(x_left, y_left, 0, rgba);
    DrawQuadTex(x_right, y_right, 0, rgba);
    DrawQuadTex(x_top, y_top, 0, rgba);
    double t_rgba[] = {0.5, 0.5, 0.5, 0.8};
    DrawTransparent(x_in, y_in, t_rgba);
}

void ViewTexture::DrawObstacles(void)
{
    for (Obstacle obs : world.layerList.at(world.currentLayer).obsList)
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
    double x[] = {0.0, double(windowXLen), double(windowXLen), 0};
    double y[] = {0.0, 0.0, double(windowYLen), double(windowYLen)};
    double rgba[] = {1.0, 1.0, 1.0, 0.75};
    DrawQuadTex(x, y, 2, rgba);
}

void ViewTexture::DrawUI()
{
    // Top layer texts that keep showing all the time in game
    // Introduction / Conclusion can be done later
    glColor3ub(0, 0, 0);
    glRasterPos2d(5, 25);
    char buffer[30];
    std::sprintf(buffer, "Current Layer: %d", world.currentLayer);
    YsGlDrawFontBitmap16x20(buffer);
}

void ViewTexture::RenderGame()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    DrawBackground(1);
    DrawObstacles();
    //    DrawHero();
    DrawForeground();
    DrawUI();
    glDisable(GL_BLEND);
}

void ViewTexture::RenderWelcome(void)
{
    glRasterPos2d(windowXLen / 2 - 32 * 6, windowYLen / 4 + 10);
    YsGlDrawFontBitmap32x48("Banana Jump!");
    glRasterPos2d(windowXLen / 2 - 16 * 12, windowYLen / 2 + 10);
    YsGlDrawFontBitmap16x20("Jump: Space");
    glRasterPos2d(windowXLen / 2 - 16 * 12, windowYLen / 2 + 40);
    YsGlDrawFontBitmap16x20("Left arrow: move left");
    glRasterPos2d(windowXLen / 2 - 16 * 12, windowYLen / 2 + 70);
    YsGlDrawFontBitmap16x20("Right arrow: move right");
    glRasterPos2d(windowXLen / 2 - 16 * 10, windowYLen / 4 * 3 + 10);
    YsGlDrawFontBitmap16x20("Press Space to Start");
}

void ViewTexture::RenderWin(void)
{
    glColor3ub(0, 0, 0);
    glRasterPos2d(windowXLen / 2 - 16 * 4, windowYLen / 2 + 10);
    YsGlDrawFontBitmap16x20("You Win!");
}