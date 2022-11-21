class Obstacle { 
    protected:
        double blx, bly;
        double xlen, ylen;
    public:
        Obstacle();
        int GetX(void);
        int GetY(void);
        int GetWidth(void);
        int GetHeight(void);
        void Generate(double X,double Y,double Width,double Height);
};

Obstacle::Obstacle() 
{ 
blx=10; 
bly=10; 
xlen=10;
ylen=10;
} 
int Obstacle::GetX(void)
{
    return blx;
}
int Obstacle::GetY(void)
{
    return bly;
}
int Obstacle::GetWidth(void)
{
    return xlen;
}
int Obstacle::GetHeight(void)
{
    return ylen;
}
void Obstacle::Generate(double X,double Y,double Width,double Height)
{
        blx=X;
        bly=Y;
        xlen=Width;
        ylen=Height;
}