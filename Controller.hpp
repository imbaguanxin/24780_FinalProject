#ifndef Controller_hpp
#define Controller_hpp

#include <chrono>

#include "Hero.hpp"

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
    int spaceState;
    double intensity;
    SpaceEvent se;
    HeroMoveDir dir;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

public:
    Controller();
    bool isGameEnd();
    SpaceEvent getSpaceEvent();
    HeroMoveDir getMoveDir();
    double getIntensity();

    void CheckKeyState(void);
};

#endif /* Controller_hpp */
