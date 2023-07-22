#ifndef _PARTICLE_
#define _PARTICLE_


#include <stdlib.h>


class Particle
{
public:

  float current_x, current_y;
  float dx, dy;

public:
  
  void respawn(float x, float y);

};


#endif
