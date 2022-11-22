#include "World.hpp"

// ================================
// hero
// ================================

// ================================
// obstacles
// ================================
Obstacle::Obstacle()
{
    blx = 10;
    bly = 10;
    xlen = 10;
    ylen = 10;
}
int Obstacle::GetX(void)
{
    return blx;
}
int Obstacle::GetY(void)
{
    return bly;
}
int Obstacle::GetXlen(void)
{
    return xlen;
}
int Obstacle::GetYlen(void)
{
    return ylen;
}
void Obstacle::Init(double X, double Y, double Width, double Height)
{
    blx = X;
    bly = Y;
    xlen = Width;
    ylen = Height;
}

// ================================
// World
// ================================
void World::Next(double time_interval)
{
    // update position of hero

    // check if hero go to a new layer

    // hit check with hero and obstacle
    // if hit, change state of hero
}

void World::MoveHero(HeroMoveDir dir)
{
}

void World::JumpHero(double instensity, HeroMoveDir dir)
{
}

void World::CheckHit(void)
{
}

void World::RenewLayer(void)
{
}