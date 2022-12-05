#include "Controller.hpp"
#include "fssimplewindow.h"
Controller::Controller()
{
    esc = false;
    spaceState = 0;
    se = spaceDefault;
    dir = stand;
    timestamp = std::chrono::system_clock::now();
}

bool Controller::IsGameEnd()
{
    return esc;
}
SpaceEvent Controller::GetSpaceEvent()
{
    return se;
}
HeroMoveDir Controller::GetMoveDir()
{
    return dir;
}
double Controller::GetIntensity(World &w)
{
    if (charging == w.hero.heroState)
    {
        return GetTimeDiff();
    }
    return 0;
}
double Controller::GetTimeDiff(void)
{
    auto now = std::chrono::system_clock::now();
    auto intensity = std::chrono::duration_cast<std::chrono::milliseconds>(now - timestamp).count() / 50;
    return double(intensity);
}

void Controller::WorldNextTick(World &w, double time_interval)
{
    if (spacePressed == se) // attempt to charge
    {
        if (w.StartCharging())
        {
            timestamp = std::chrono::system_clock::now();
            hasJumpBeforeSpaceReleased = false;
            return;
        }
        else
        {
            w.CalcNext(time_interval);
            return;
        }
    }
    else if (spaceReleased == se) // attempt to jump
    {
        if (hasJumpBeforeSpaceReleased)
        {
            w.CalcNext(time_interval);
            hasJumpBeforeSpaceReleased = false;
            return;
        }
        else
        {
            double intensity = GetTimeDiff();
            if (!w.JumpHero(intensity, dir))
            {
                w.CalcNext(time_interval);
            }
        }
    }
    else if (spaceDefault == se) // no space event
    {
        double intensity = GetIntensity(w);
        if (intensity >= maxIntensity) // if charging to max
        {
            if (w.JumpHero(intensity, dir)) // attemp to jump
            {
                hasJumpBeforeSpaceReleased = true;
            }
            else
            {
                w.CalcNext(time_interval);
            }
        }
        else if (moveLeft == dir)
        {
            if (!w.MoveHeroLeftOnLand(time_interval))
            {
                w.CalcNext(time_interval);
            }
        }
        else if (moveRight == dir)
        {
            if (!w.MoveHeroRightOnLand(time_interval))
            {
                w.CalcNext(time_interval);
            }
        }
        else
        {
            w.CalcNext(time_interval);
        }
    }
}

void Controller::CheckKeyState(void)
{
    FsPollDevice();
    int key = FsInkey();
    if (FSKEY_ESC == key)
    {
        esc = true;
    }

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
        { // previously not pressed
            se = spacePressed;
            timestamp = std::chrono::system_clock::now();
        }
        else
        { // previously pressed
            se = spaceReleased;
        }
        spaceState = nowSpaceState;
    }
    else
    {
        se = spaceDefault;
    }
}

void Controller::UpdateGameStage(World &w)
{
    if (gameStage == 0) {
        FsPollDevice();
        int key = FsInkey();
        if (FSKEY_ESC == key)
        {
            esc = true;
        } else if (FSKEY_SPACE == key) {
            gameStage = 1;
        }
    } else if (gameStage == 2) {
        if (w.CheckWin()) {
            gameStage = 2;
        }
    } else {
        FsPollDevice();
        int key = FsInkey();
        if (FSKEY_ESC == key)
        {
            esc = true;
        }
    }
}
