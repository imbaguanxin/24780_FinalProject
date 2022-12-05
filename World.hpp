#ifndef World_hpp
#define World_hpp

#include <vector>
#include "Hero.hpp"
#include "Layer.hpp"
#include "Obstacle.hpp"
// #include "Controller.hpp"
class World
{
public:
    Hero hero;
    std::vector<Layer> layerList;
    int currentLayer;
    double layerXLen, layerYLen;
    bool isWin = false;

    World(void);
    ~World(void);
    void MoveHeroOnAir(double time_interval);
    // allowed attempts:
    bool JumpHero(double instensity, HeroMoveDir dir);
    bool MoveHeroLeftOnLand(double time_interval);
    bool MoveHeroRightOnLand(double time_interval);
    bool StartCharging();
    // calculate next step (on air)
    void CalcNext(double time_interval);

protected:
    // physical simulation
    void CheckHitObstacle(void);
    void CheckHitEdge(void);
    void RenewLayer(void);
    void CheckDropObstacle(void);
    void CheckWin(void);
    const int hero_move_speed = 5; // move speed of hero
};

#endif /* World_hpp */
