#include "tile.hpp"

Tile::Tile(int x, int y, int type, int width, int height, int hitpoints)
{
  this->rectangle.x = x;
  this->rectangle.y = y;
  this->rectangle.w = width;
  
  this->rectangle.h = height;
  
  this->index_in_texture = type;
  this->hitpoints = hitpoints;


}
