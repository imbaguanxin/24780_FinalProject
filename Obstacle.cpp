#include "Obstacle.hpp"

Obstacle::Obstacle()
{
    Init(0, 0, 0, 0);
}
Obstacle::Obstacle(double x, double y, double x_len, double y_len)
{
    Init(x, y, x_len, y_len);
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
void Obstacle::Init(double x, double y, double x_len, double y_len)
{
    blx = x;
    bly = y;
    xlen = x_len;
    ylen = y_len;
}
