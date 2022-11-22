#include "World.hpp"

World::World()
{
    current_layer = 0;
}

void World::Next(double time_interval)
{
    // update position of hero

    // check if hero go to a new layer

    // hit check with hero and obstacle
    // if hit, change state of hero
}

void World::MoveHero(HeroMoveDir dir)
{
}

void World::JumpHero(double instensity, HeroMoveDir dir)
{
}

void World::CheckHit(void) //(double x, double y)
{
    // layer.initialize_obs(current_layer); // judge which layer it is and initialize the layer's obs.
    // int relativeX, relativeY;
    // relativeX = x - obstacleX;
    // relativeY = y - obstacleY;
    // for (int i = 0; i < 6; i++)
    // {
    //     if (here.heroState == 1 && 0 <= relativeX && relativeX < layer.obs_list[i].GetWidth() && 0 <= relativeY && relativeY < layer.obs_list[i].GetHeight())
    //     {
    //         return 1;
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }
}

void World::RenewLayer(void)
{
    // if (hero.y + hero.redius > layer.ylen)
    // {
    //     current_layer++;
    // }
}
