#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include "map.hpp"
#include "camera.hpp"

class Sprite {

public:
  SDL_Texture* texture;
  SDL_Rect rectangle;

  const char* original_path, *new_path;

  bool is_falling;

  int speed;

  enum direction {
    LEFT = -1,
    RIGHT = 1,
  };

  
public:
  
  Sprite(SDL_Renderer *renderer,  const char* path, int x, int y);

  void scale(float scalar);

  bool is_hover();
  
    void render(SDL_Renderer *renderer, Camera &camera, bool &is_looking_right);

  void move(int& speed, direction dir, Map &map);

  void apply_collisions(float& speed, Map &new_map, bool& is_jumping);
};

#endif
