#include "Controller.hpp"
#include "fssimplewindow.h"
Controller::Controller()
{
    esc = false;
    spaceState = 0;
    intensity = 0;
    se = spaceDefault;
    dir = stand;
    timestamp = std::chrono::system_clock::now();
}

bool Controller::isGameEnd()
{
    return esc;
}
SpaceEvent Controller::getSpaceEvent()
{
    return se;
}
HeroMoveDir Controller::getMoveDir()
{
    return dir;
}
double Controller::getIntensity()
{
    return intensity;
}

void Controller::CheckKeyState(void)
{
    FsPollDevice();
    int key = FsInkey();
    if (FSKEY_ESC == key)
    {
        esc = true;
    }
    intensity = 0;

    int nowLeftState = FsGetKeyState(FSKEY_LEFT);
    int nowRightState = FsGetKeyState(FSKEY_RIGHT);
    if (nowLeftState)
    {
        dir = moveLeft;
    }
    else if (nowRightState)
    {
        dir = moveRight;
    }
    else
    {
        dir = stand;
    }

    int nowSpaceState = FsGetKeyState(FSKEY_SPACE);
    if (nowSpaceState != spaceState)
    {
        if (0 == spaceState)
        {
            se = spacePressed;
            timestamp = std::chrono::system_clock::now();
        }
        else
        {
            se = spaceReleased;
            auto now = std::chrono::system_clock::now();
            intensity = std::chrono::duration_cast<std::chrono::milliseconds>(now - timestamp).count() / 50;
        }
        spaceState = nowSpaceState;
    }
    else
    {
        se = spaceDefault;
    }
}
