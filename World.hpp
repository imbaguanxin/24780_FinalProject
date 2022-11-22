#include "Hero.hpp"

#ifndef STD_VECTOR_IS_INCLUDED
#include <vector>
#define STD_VECTOR_IS_INCLUDED
#endif

#include "Layer.hpp"

enum HeroMoveDir {
    moveLeft, moveRight
}

class World
{
    public:
        Hero hero;
        std::vector<Layer> layer_list;
        int current_layer;

        void move_hero(HeroMoveDir dir);
        void jump_hero(double intensity, HeroMoveDir dir);
        void next(double time_interval);
    
    protected:
        // obstcle* binded_obstacle;
    // physical simulation
        void check_hit(void);
        void renew_layer(void);
    // more functions here
    // TODO:
};

void World::next(double time_interval){
    // update position of hero

    // check if hero go to a new layer

    // hit check with hero and obstacle
    // if hit, change state of hero
}
