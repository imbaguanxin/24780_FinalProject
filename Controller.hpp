#ifndef Controller_hpp
#define Controller_hpp

#include <chrono>

#include "Hero.hpp"
#include "World.hpp"

enum SpaceEvent
{
    spaceDefault,
    spacePressed,
    spaceReleased
};

class Controller
{
protected:
    bool esc = false;
    bool hasJumpBeforeSpaceReleased = false;
    int spaceState;
    SpaceEvent se;
    HeroMoveDir dir;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    const double maxIntensity = 30; // max speed vy: 30 m/s
    const double chargingSpeed = 0.03; // 0.02 m/ms^2
    double GetTimeDiff(void);

public:
    int gameStage = 0;
    Controller();
    bool IsGameEnd();
    SpaceEvent GetSpaceEvent();
    HeroMoveDir GetMoveDir();
    double GetIntensity(World &w);
    double GetIntensityPercent(World &w);
    void CheckKeyState(void);
    void WorldNextTick(World &w, double time_interval);
    void UpdateGameStage(World &w);
};

#endif /* Controller_hpp */
