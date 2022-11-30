#ifndef Obstacle_hpp
#define Obstacle_hpp

class Obstacle
{
protected:
    // lower left position
    double blx, bly;
    double xlen, ylen;

public:
    int state;
    Obstacle();
    Obstacle(double x, double y, double x_len, double y_len, int state);
    double GetX(void);
    double GetY(void);
    double GetXlen(void);
    double GetYlen(void);
    void Init(double x, double y, double x_len, double y_len, int state_obs);
};

#endif
