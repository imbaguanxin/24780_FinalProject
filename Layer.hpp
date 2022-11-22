#ifndef STD_VECTOR_IS_INCLUDED
#include <vector>
#define STD_VECTOR_IS_INCLUDED
#endif

#ifndef OBSTACLE_IS_INCLUDED
#include "Obstacle.hpp"
#define OBSTACLE_IS_INCLUDED
#endif

class Layer
{
public:
    int layer_num;
    double xlen, ylen;
    std::vector<Obstacle> obs_list[6];
    double obs_x[12];        // The original point of the image window is the left bottum conner
    double obs_y[12];        // The original point of the obstacle is the center point
    double obs_width[12];    // now temporary design 2 layers' elements and each layer has 6 obstacles
    double obs_height[12];
    Layer();
    void initialize_obs(void);
};
Layer::Layer()
{  
   layer_num = 0;
   xlen = 1000.0;
   ylen = 1000.0;
   obs_x[12] = {125,875,500,125,680,310,700,300,600,350,850,550};
   obs_y[12] = {125,125,500,650,800,900,100,250,400,650,650,850};
   obs_width[12] = {250,250,200,175,220,235,200,100,300,250,300,100};
   obs_height[12] = {250,250,100,50,120,150,100,50,150,130,200,50};
}
void Layer::initialize_obs(void)
{
    for(int i=0;i<sizeof(obs_list);i++)
    {
        obs_list[i].Generate(obs_x[layer_num*6+i],obs_y[layer_num*6+i],obs_width[layer_num*6+i],obs_height[layer_num*6+i]);
    }
}
