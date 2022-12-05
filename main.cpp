#include "World.hpp"
#include "View.hpp"
#include "fssimplewindow.h"
#include "Controller.hpp"
#include "ViewTexture.hpp"
#include "yspng.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <chrono>

void CreateView(View4Test &v, std::string filename)
{
    std::ifstream file;
    std::string line, word;
    double x, y, xlen, ylen, radius;
    int layer = -1;
    int total_layer = -1;
    file.open(filename);

    while (std::getline(file, line))
    {
        std::istringstream linestream(line);
        linestream >> word;
        if ("windowsize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.windowXLen = int(x);
            v.windowYLen = int(y);
            printf("window size: x:%d, y:%d\n", v.windowXLen, v.windowYLen);
        }
        else if ("layersize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.world.layerXLen = x;
            v.world.layerYLen = y;
            printf("layersize: x:%f, y:%f\n", v.world.layerXLen, v.world.layerYLen);
        }
        else if ("hero" == word)
        {
            linestream >> x;
            linestream >> y;
            linestream >> radius;
            v.world.hero.x = x;
            v.world.hero.y = y;
            v.world.hero.radius = radius;
            printf("hero: x:%f, y:%f, radius:%f\n", v.world.hero.radius, v.world.hero.y, radius);
        }
        else if ("totallayer" == word)
        {
            linestream >> total_layer;
            for (int i = 0; i < total_layer; ++i)
            {
                Layer l;
                v.world.layerList.push_back(l);
            }
            printf("total layer: %lu\n", v.world.layerList.size());
        }
        else if ("layer" == word)
        {
            linestream >> layer;
            printf("layer: %d\n", layer);
        }
        else if ("obstacle" == word)
        {
            linestream >> x;
            linestream >> y;
            linestream >> xlen;
            linestream >> ylen;
            Obstacle obs(x, y, xlen, ylen, 0);
            v.world.layerList.at(layer).obsList.push_back(obs);
            printf("layer: %d, obstacle: %lf, %lf, %lf, %lf\n", layer, x, y, xlen, ylen);
        }
    }
    file.close();
    if (v.world.layerList.size() != total_layer)
    {
        std::cout << "total layer and claimed layer not match" << std::endl;
    }
    v.world.currentLayer = 0;
}

void CreateViewTexture(ViewTexture &v, std::string filename)
{
    std::ifstream file;
    std::string line, word;
    double x, y, xlen, ylen, radius;
    int layer = -1;
    int total_layer = -1;
    file.open(filename);

    while (std::getline(file, line))
    {
        std::istringstream linestream(line);
        linestream >> word;
        if ("windowsize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.windowXLen = int(x);
            v.windowYLen = int(y);
            printf("window size: x:%d, y:%d\n", v.windowXLen, v.windowYLen);
        }
        else if ("layersize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.world.layerXLen = x;
            v.world.layerYLen = y;
            printf("layersize: x:%f, y:%f\n", v.world.layerXLen, v.world.layerYLen);
        }
        else if ("hero" == word)
        {
            linestream >> x;
            linestream >> y;
            linestream >> radius;
            v.world.hero.x = x;
            v.world.hero.y = y;
            v.world.hero.radius = radius;
            printf("hero: x:%f, y:%f, radius:%f\n", v.world.hero.radius, v.world.hero.y, radius);
        }
        else if ("totallayer" == word)
        {
            linestream >> total_layer;
            for (int i = 0; i < total_layer; ++i)
            {
                Layer l;
                v.world.layerList.push_back(l);
            }
            printf("total layer: %lu\n", v.world.layerList.size());
        }
        else if ("layer" == word)
        {
            linestream >> layer;
            printf("layer: %d\n", layer);
        }
        else if ("obstacle" == word)
        {
            linestream >> x;
            linestream >> y;
            linestream >> xlen;
            linestream >> ylen;
            Obstacle obs(x, y, xlen, ylen, 0);
            v.world.layerList.at(layer).obsList.push_back(obs);
            printf("layer: %d, obstacle: %lf, %lf, %lf, %lf\n", layer, x, y, xlen, ylen);
        }
    }
    file.close();
    if (v.world.layerList.size() != total_layer)
    {
        std::cout << "total layer and claimed layer not match" << std::endl;
    }
    v.world.currentLayer = 0;
}

void main4Test()
{
    FsChangeToProgramDir();

    View4Test v;

    CreateView(v, "config.txt");

    auto now = std::chrono::system_clock::now();
    auto next_now = std::chrono::system_clock::now();
    double time_interval = 0;

    FsOpenWindow(16, 16, v.windowXLen, v.windowYLen, 1);
    Controller c;
    while (!c.IsGameEnd())
    {
        next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000;
        now = next_now;

        c.CheckKeyState();
        c.WorldNextTick(v.world, time_interval);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        v.Render();
        FsSwapBuffers();
        FsSleep(20);
    }
}

void main4Texture()
{
    FsChangeToProgramDir();

    ViewTexture v;

    CreateViewTexture(v, "config.txt");
    TextureData texD(6);
    v.texData = &texD;
    v.texData->decoders[0].Decode("grass3.png");
    v.texData->decoders[1].Decode("background2.png");
    v.texData->decoders[2].Decode("foreground2.png");
    v.texData->decoders[3].Decode("banana_l.png");
    v.texData->decoders[4].Decode("banana_r.png");
    v.texData->decoders[5].Decode("banana_air.png");
    // 0: texture for obstacles
    // 1: background
    // 2: foreground
    // 3,4,5 -> hero left, hero right, hero on air
    float color[] = {
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
    };
    v.texData->setRGBA(color);

    auto now = std::chrono::system_clock::now();
    auto next_now = std::chrono::system_clock::now();
    double time_interval = 0;

    FsOpenWindow(16, 16, v.windowXLen, v.windowYLen, 1);

    Controller c;
    v.InitTexture();
    while (!c.IsGameEnd())
    {   
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        switch (c.gameStage) {
            case 0:
                v.RenderWelcome();
                c.UpdateGameStage(v.world);
                break;
            case 1:
                next_now = std::chrono::system_clock::now();
                time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000;
                now = next_now;
                c.CheckKeyState();
                c.WorldNextTick(v.world, time_interval);
                v.RenderGame(c.GetIntensityPercent(v.world));
                c.UpdateGameStage(v.world);
                break;
            case 2:
                c.CheckKeyState();
                v.RenderWin();
                break;
            default:
                break;
        }
        FsSwapBuffers();
        FsSleep(20);
    }
}

int main()
{
//    main4Test();
        main4Texture();
    return 0;
}
