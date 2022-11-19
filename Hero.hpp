enum HeroState
{
    onLand,
    onAir,
    charging,
}

class Hero
{
public:
    double x, y;
    double vx, vy;
    double radius;
    HeroState heroState;
}