#include "World.hpp"

World::World(void)
{
    current_layer = 0;
    layer_x_len = 0;
    layer_y_len = 0;
}

World::~World(void)
{
}


void World::Next(double time_interval, HeroMoveDir dir, double intensity)
{
    if (intensity > 0 && hero.heroState == charging)
    {
        JumpHero(intensity, dir);
        for (Obstacle &obs : layer_list.at(current_layer).obs_list)
        {
            obs.state = 0;
        }
    }
    // update position of hero
    switch (hero.heroState) {
    case onAir:
        MoveHeroOnAir(time_interval);
        // hit check with hero and obstacle
        CheckHitObstacle();
        break;

    case onLand:
        MoveHeroOnLand(dir, time_interval);
        // drop check with hero and obstacle
        CheckDropObstacle();
        break;

    case charging:
        break;

    default:
        printf("State failed, your state is: %d\n", hero.heroState);
        break;
    }
    // check if hero go to a new layer
    RenewLayer();
    // hit check with hero and edge
    // if hit, change state of hero
    CheckHitEdge();
}

void World::MoveHeroOnLand(HeroMoveDir dir, double time_interval)
{
    hero.heroDir = dir;
    switch(dir) {
    case moveLeft:
        hero.x -= 1 * time_interval;
        break;
    case moveRight:
        hero.x += 1 * time_interval;
        break;
    default:
        break;
    }
}

void World::MoveHeroOnAir(double time_interval)
{
    hero.y += hero.vy * time_interval;
    hero.x += hero.vx * time_interval;
    hero.vy -= hero.ay * time_interval;
}

void World::JumpHero(double intensity, HeroMoveDir dir)
{
    hero.heroState = onAir;
    hero.heroDir = dir;
    hero.vy += intensity;
    
    switch (dir) {
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
}

void World::CheckHitObstacle(void)
{
    for (Obstacle &obs : layer_list.at(current_layer).obs_list) // also detect current layer + 1 and current layer - 1 ?
    {
        double dx, dy;
        dx = hero.x - obs.GetX();
        dy = hero.y - obs.GetY();
        if (dx >= 0 && dx <= obs.GetXlen() && dy <= obs.GetYlen() + hero.radius && dy >= 0.5 * obs.GetYlen()) {
            printf("Hit from top\n");
            hero.y = obs.GetY() + obs.GetYlen() + hero.radius;
            hero.heroState = onLand;
            hero.vx = 0;
            hero.vy = 0;
            hero.heroDir = stand;
            obs.state = 1;
        } else if (dx >= 0 && dx <= obs.GetXlen() && dy < 0.5 * obs.GetYlen() && dy >= -hero.radius) {
            printf("Hit from bottom!\n");
            hero.y = obs.GetY() - hero.radius; // hit from bottom
            hero.vy = -hero.vy;
        }
        else if (dx < 0 && dx >= -hero.radius && dy >= 0 && dy <= obs.GetYlen() ) // hit from left
        {
            printf("Hit from left!\n");
            hero.x = obs.GetX() - hero.radius;
            hero.vx = -hero.vx;
        }
        else if (dx > obs.GetXlen() && dx <= hero.radius + obs.GetXlen() && dy >= 0 && dy <= obs.GetYlen() ) // hit from right
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
        else if (hero.x >= layer_x_len - hero.radius)
        {
            hero.x = layer_x_len - hero.radius;
        }
        break;
    case onAir:
        if (hero.x <= hero.radius)
        {
            hero.vx = -hero.vx;
        }
        else if (hero.x >= layer_x_len - hero.radius)
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
    current_layer = (int)hero.y / layer_y_len;
}

void World::CheckDropObstacle(void)
{
    for (Obstacle &obs : layer_list.at(current_layer).obs_list)
    {
        if (obs.state == 0) continue;
        if (hero.x < obs.GetX() - 0.5 * hero.radius) {
            obs.state = 0;
            JumpHero(0, moveLeft);
        } else if (hero.x > obs.GetX() + obs.GetXlen() + 0.5 * hero.radius) {
            obs.state = 0;
            JumpHero(0, moveRight);
        }
    }
}
