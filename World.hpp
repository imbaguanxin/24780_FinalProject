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

    World(void);
    ~World(void);
    void MoveHeroOnLand(HeroMoveDir dir, double time_interval);
    void MoveHeroOnAir(double time_interval);
    void JumpHero(double instensity, HeroMoveDir dir);
    void Next(double time_interval, HeroMoveDir dir, double intensity);

protected:
    // physical simulation
    void CheckHitObstacle(void);
    void CheckHitEdge(void);
    void RenewLayer(void);
    // more functions here
    void CheckDropObstacle(void);
};

#endif /* World_hpp */
