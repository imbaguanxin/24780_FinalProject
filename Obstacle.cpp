#include "Obstacle.hpp"

Obstacle::Obstacle()
{
    Init(0, 0, 0, 0, 0);
}
Obstacle::Obstacle(double x, double y, double x_len, double y_len, int state_obs)
{
    Init(x, y, x_len, y_len, state_obs);
}
double Obstacle::GetX(void)
{
    return blx;
}
double Obstacle::GetY(void)
{
    return bly;
}
double Obstacle::GetXlen(void)
{
    return xlen;
}
double Obstacle::GetYlen(void)
{
    return ylen;
}
void Obstacle::Init(double x, double y, double x_len, double y_len, int state_obs)
{
    blx = x;
    bly = y;
    xlen = x_len;
    ylen = y_len;
    state = state_obs;
}
