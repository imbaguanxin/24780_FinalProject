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
            v.window_x_len = int(x);
            v.window_y_len = int(y);
            printf("window size: x:%d, y:%d\n", v.window_x_len, v.window_y_len);
        }
        else if ("layersize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.world.layer_x_len = x;
            v.world.layer_y_len = y;
            printf("layersize: x:%f, y:%f\n", v.world.layer_x_len, v.world.layer_y_len);
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
                v.world.layer_list.push_back(l);
            }
            printf("total layer: %lu\n", v.world.layer_list.size());
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
            v.world.layer_list.at(layer).obs_list.push_back(obs);
            printf("layer: %d, obstacle: %lf, %lf, %lf, %lf\n", layer, x, y, xlen, ylen);
        }
    }
    file.close();
    if (v.world.layer_list.size() != total_layer)
    {
        std::cout << "total layer and claimed layer not match" << std::endl;
    }
    v.world.current_layer = 0;
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
            v.window_x_len = int(x);
            v.window_y_len = int(y);
            printf("window size: x:%d, y:%d\n", v.window_x_len, v.window_y_len);
        }
        else if ("layersize" == word)
        {
            linestream >> x;
            linestream >> y;
            v.world.layer_x_len = x;
            v.world.layer_y_len = y;
            printf("layersize: x:%f, y:%f\n", v.world.layer_x_len, v.world.layer_y_len);
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
                v.world.layer_list.push_back(l);
            }
            printf("total layer: %lu\n", v.world.layer_list.size());
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
            v.world.layer_list.at(layer).obs_list.push_back(obs);
            printf("layer: %d, obstacle: %lf, %lf, %lf, %lf\n", layer, x, y, xlen, ylen);
        }
    }
    file.close();
    if (v.world.layer_list.size() != total_layer)
    {
        std::cout << "total layer and claimed layer not match" << std::endl;
    }
    v.world.current_layer = 0;
}

void main4Test()
{
    FsChangeToProgramDir();

    View4Test v;

    CreateView(v, "config.txt");

    auto now = std::chrono::system_clock::now();

    double time_interval = 0;
    double intensity = 0;
    HeroMoveDir dir = stand;
    SpaceEvent se = spaceDefault;

    FsOpenWindow(16, 16, v.window_x_len, v.window_y_len, 1);
    Controller c;
    while (!c.isGameEnd())
    {
        auto next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000;
        now = next_now;

        c.CheckKeyState();
        dir = c.getMoveDir();
        intensity = c.getIntensity();
        se = c.getSpaceEvent();

        v.Next(time_interval, se, dir, intensity);
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
    TextureData texD(3);
    v.texData = &texD;
    v.texData->decoders[0].Decode("grass3.png");
    v.texData->decoders[1].Decode("background2.png");
    v.texData->decoders[2].Decode("foreground2.png");
    float color[] = {
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0
    };
    v.texData->setRGBA(color);

    auto now = std::chrono::system_clock::now();

    double time_interval = 0;
    double intensity = 0;
    HeroMoveDir dir = stand;
    SpaceEvent se = spaceDefault;

    FsOpenWindow(16, 16, v.window_x_len, v.window_y_len, 1);

    Controller c;
    v.InitTexture();
    while (!c.isGameEnd())
    {
        auto next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000;
        now = next_now;

        c.CheckKeyState();
        dir = c.getMoveDir();
        intensity = c.getIntensity();
        se = c.getSpaceEvent();

        v.Next(time_interval, se, dir, intensity);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        v.Render();
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
