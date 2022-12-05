#include "World.hpp"

World::World(void)
{
    currentLayer = 0;
    layerXLen = 0;
    layerYLen = 0;
}

World::~World(void)
{
}

void World::MoveHeroOnAir(double time_interval)
{
    if (CheckWin())
        return;
    hero.y += hero.vy * time_interval;
    hero.x += hero.vx * time_interval;
    hero.vy -= hero.ay * time_interval;
}

bool World::JumpHero(double intensity, HeroMoveDir dir)
{
    if (CheckWin())
        return false;
    if (charging != hero.heroState)
        return false;
    hero.heroState = onAir;
    hero.heroDir = dir;
    hero.vy += intensity;

    switch (dir)
    {
    case moveLeft:
        hero.vx = -hero.jumpSpeed;
        break;
    case moveRight:
        hero.vx = hero.jumpSpeed;
        break;
    case stand:
        hero.vx = 0;
        break;
    default:
        printf("Direction failed, your direction is %d\n", dir);
        break;
    }
    return true;
}

bool World::MoveHeroRightOnLand(double time_interval)
{
    if (CheckWin())
        return false;
    if (hero.heroState != onLand)
    {
        return false;
    }
    hero.x += hero_move_speed * time_interval;
    RenewLayer();
    CheckDropObstacle();
    CheckHitEdge();
    return true;
}

bool World::MoveHeroLeftOnLand(double time_interval)
{
    if (CheckWin())
        return false;
    if (hero.heroState != onLand)
    {
        return false;
    }
    hero.x -= hero_move_speed * time_interval;
    RenewLayer();
    CheckDropObstacle();
    CheckHitEdge();
    return true;
}

bool World::StartCharging()
{
    if (CheckWin())
        return false;
    if (onLand != hero.heroState)
    {
        return false;
    }
    hero.heroState = charging;
    return true;
}

void World::CalcNext(double time_interval)
{
    if (CheckWin())
        return;
    if (hero.heroState != onAir)
    {
        return;
    }
    MoveHeroOnAir(time_interval);
    CheckHitObstacle();
    RenewLayer();
    CheckHitEdge();
}

void World::CheckHitObstacle(void)
{
    if (CheckWin())
        return;
    for (Obstacle &obs : layerList.at(currentLayer).obsList) // also detect current layer + 1 and current layer - 1 ?
    {
        double dx, dy;
        dx = hero.x - obs.GetX();
        dy = hero.y - obs.GetY();
        if (dx >= 0 && dx <= obs.GetXlen() && dy <= obs.GetYlen() + hero.radius && dy >= 0.5 * obs.GetYlen())
        {
            printf("Hit from top\n");
            hero.y = obs.GetY() + obs.GetYlen() + hero.radius;
            hero.heroState = onLand;
            hero.vx = 0;
            hero.vy = 0;
            hero.heroDir = stand;
            obs.state = 1;
            CheckWin();
        }
        else if (dx >= 0 && dx <= obs.GetXlen() && dy < 0.5 * obs.GetYlen() && dy >= -hero.radius)
        {
            printf("Hit from bottom!\n");
            hero.y = obs.GetY() - hero.radius; // hit from bottom
            CheckWin();
            hero.vy = -hero.vy;
        }
        else if (dx < 0 && dx >= -hero.radius && dy >= 0 && dy <= obs.GetYlen()) // hit from left
        {
            printf("Hit from left!\n");
            hero.x = obs.GetX() - hero.radius;
            hero.vx = -hero.vx;
        }
        else if (dx > obs.GetXlen() && dx <= hero.radius + obs.GetXlen() && dy >= 0 && dy <= obs.GetYlen()) // hit from right
        {
            printf("Hit from right!\n");
            hero.x = obs.GetX() + obs.GetXlen() + hero.radius;
            hero.vx = -hero.vx;
        }
    }
}

void World::CheckHitEdge(void) //(double x, double y)
{
    switch (hero.heroState)
    {
    case onLand:
        if (hero.x <= hero.radius)
        {
            hero.x = hero.radius;
        }
        else if (hero.x >= layerXLen - hero.radius)
        {
            hero.x = layerXLen - hero.radius;
        }
        break;
    case onAir:
        if (hero.x <= hero.radius)
        {
            hero.vx = -hero.vx;
        }
        else if (hero.x >= layerXLen - hero.radius)
        {
            hero.vx = -hero.vx;
        }
        break;
    case charging:
        break;
    default:
        printf("State failed, your state is: %d\n", hero.heroState);
        break;
    }
}

void World::RenewLayer(void)
{
    currentLayer = (int)hero.y / layerYLen;
    isWin = currentLayer < 0 || currentLayer >= layerList.size();
}

void World::CheckDropObstacle(void)
{
    if (CheckWin())
        return;
    for (Obstacle &obs : layerList.at(currentLayer).obsList)
    {
        if (obs.state == 0)
            continue;
        if (hero.x < obs.GetX())
        {
            printf("go to edge left\n");
            hero.heroState = charging;
            obs.state = 0;
            JumpHero(0, moveLeft);
        }
        else if (hero.x > obs.GetX() + obs.GetXlen())
        {
            printf("go to edge right\n");
            hero.heroState = charging;
            obs.state = 0;
            JumpHero(0, moveRight);
        }
    }
}

bool World::CheckWin()
{
    if (!isWin)
        RenewLayer();
    return isWin;
}
