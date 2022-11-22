#ifndef Obstacle_hpp
#define Obstacle_hpp

class Obstacle
{
protected:
    // lower left position
    double blx, bly;
    double xlen, ylen;

public:
    Obstacle();
    Obstacle(double x, double y, double x_len, double y_len);
    double GetX(void);
    double GetY(void);
    double GetXlen(void);
    double GetYlen(void);
    void Init(double x, double y, double x_len, double y_len);
};

#endif

