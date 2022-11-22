#ifndef World_hpp
#define World_hpp

#include <vector>
#include "Hero.hpp"
#include "Layer.hpp"
#include "Obstacle.hpp"

class World
{
public:
    Hero hero;
    std::vector<Layer> layer_list;
    int current_layer;
    double layer_x_len, layer_y_len;

    
    void MoveHero(HeroMoveDir dir);
    void JumpHero(double instensity, HeroMoveDir dir);
    void Next(double time_interval);

protected:
    // obstcle* binded_obstacle;
    // physical simulation
    void CheckHit(void);
    void RenewLayer(void);
    // more functions here
    // TODO:
};


#endif /* World_hpp */
