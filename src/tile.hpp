#ifndef _TILE_H
#define _TILE_H

#include <SDL2/SDL.h>

enum block_type {
  AIR,
  DIRT,
  STONE

};



class Tile
{
public:
  SDL_Rect rectangle;

  int index_in_texture;
  int hitpoints;

  
public:

  Tile(int x, int y, int type, int width, int height, int hitpoints);

  void render(SDL_Renderer* renderer);

};


#endif
