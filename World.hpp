#include "Hero.hpp"

#ifndef STD_VECTOR_IS_INCLUDED
#include <vector>
#define STD_VECTOR_IS_INCLUDED
#endif

#include "Layer.hpp"
#include "Obstacle.hpp"

enum HeroMoveDir {
    moveLeft, moveRight
}

class World
{
    public:
        Hero hero;
        Layer layer;
        std::vector<Layer> layer_list;
        int current_layer;

        void move_hero(HeroMoveDir dir);
        void jump_hero(double intensity, HeroMoveDir dir);
        void next(double time_interval);
        World();
    
    protected:
        // obstcle* binded_obstacle;
    // physical simulation
        int check_hit(double x,double y);
        void renew_layer(void);
    // more functions here
    // TODO:
};
World::World()
{
    current_layer = 0;
}

void World::next(double time_interval){
    // update position of hero

    // check if hero go to a new layer

    // hit check with hero and obstacle
    // if hit, change state of hero
}

void World::move_hero(HeroMoveDir dir) {

}

void World::jump_hero(double instensity, HeroMoveDir dir) {

}

int World::check_hit(double x,double y) {
    layer.initialize_obs(current_layer);   // judge which layer it is and initialize the layer's obs.
    int relativeX,relativeY;
    relativeX=x-obstacleX;
    relativeY=y-obstacleY;
    for(int i=0;i<6;i++)
    {
    if(here.heroState==1 && 0<=relativeX && relativeX<layer.obs_list[i].GetWidth() && 0<=relativeY && relativeY<layer.obs_list[i].GetHeight())
    {
        return 1;
    }
    else
    {
        return 0;
    }
    }
}

void World::renew_layer(void) {
     if(hero.y+hero.redius>layer.ylen)
     {
        current_layer++;
     }
}
