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
    std::vector<Layer> layerList;
    int currentLayer;
    double layerXLen, layerYLen;

    World(void);
    ~World(void);
    // allowed attempts:
    bool JumpHero(double instensity, HeroMoveDir dir);
    bool MoveHeroLeftOnLand(double time_interval);
    bool MoveHeroRightOnLand(double time_interval);
    bool StartCharging();
    // calculate next step (on air)
    void CalcNext(double time_interval);
    // check is win
    bool CheckWin(void);

protected:
    // physical simulation
    void MoveHeroOnAir(double time_interval);
    void CheckHitObstacle(void);
    void CheckHitEdge(void);
    void RenewLayer(void);
    void CheckDropObstacle(void);
    const int hero_move_speed = 5; // move speed of hero
    bool isWin = false;
};

#endif /* World_hpp */
