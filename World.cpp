#include "World.hpp"
#include <math.h>

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
    hero.heroDir = moveRight;
    hero.x += heroMoveSpeed * time_interval;
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
    hero.heroDir = moveLeft;
    hero.x -= heroMoveSpeed * time_interval;
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
        double x=0, y=0, theta=0, c=0, rdx=0;
        if (dx >= 0 && dx <= obs.GetXlen() && dy <= obs.GetYlen() + hero.radius && dy >= 0.5 * obs.GetYlen())
        {
            printf("Hit from top!\n");
            hero.y = obs.GetY() + obs.GetYlen() + hero.radius;
            hero.heroState = onLand;
            hero.vx = 0;
            hero.vy = 0;
//            hero.heroDir = stand;
            obs.state = 1;
        }
        else if (dx >= 0 && dx <= obs.GetXlen() && dy < 0.5 * obs.GetYlen() && dy >= -hero.radius)
        {
            printf("Hit from bottom!\n");
            hero.y = obs.GetY() - hero.radius; // hit from bottom
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
        else if (dx < 0 && dx >= -hero.radius && dy >= -hero.radius && dy < 0) {
            // physics behind this:
            // obey 2 formula:
            // new_vx, new_vy = vx + c * x, vx + c * y
            // nex_vx^2 + new_vy^2 = vx^2 + vy^2
            // where (x,y) is the unit vector of collesion direction.
            if (sqrt(dx * dx + dy * dy) < hero.radius) {
                printf("Hit from left corner!\n");
                theta = atan2(dy, dx);
                y = sin(theta) * hero.radius;
                x = cos(theta) * hero.radius;
                printf("theta, x, y: %f, %f, %f\n", theta, x, y);
                c = -2 * (x * hero.vx + y * hero.vy) / (hero.radius * hero.radius);
                hero.vx += c * x;
                hero.vy += c * y;
                hero.x = obs.GetX() + x;
                hero.y = obs.GetY() + y;
            }
        }
        else if (dx > obs.GetXlen() && dx <= hero.radius + obs.GetXlen() && dy >= -hero.radius && dy < 0) {
            rdx = dx - obs.GetXlen();
            if (sqrt(rdx * rdx + dy * dy) < hero.radius) {
                printf("Hit from right corner!\n");
                theta = atan2(dy, rdx);
                y = sin(theta) * hero.radius;
                x = cos(theta) * hero.radius;

                c = -2 * (x * hero.vx + y * hero.vy) / (hero.radius * hero.radius);
                hero.vx += c * x;
                hero.vy += c * y;
                hero.x = obs.GetX() + obs.GetXlen() + x;
                hero.y = obs.GetY() + y;
            }
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
