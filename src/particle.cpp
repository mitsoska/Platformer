#include "particle.hpp"

void Particle::respawn(float x, float y)
{
  this->dx = -25 + rand() % 70;
  this->dy = -25 + rand() % 70;

  this->current_x = x;
  this->current_y = y;
}
