#ifndef _CAMERA_H
#define _CAMERA_H


#include <SDL2/SDL.h>

class Camera
{

public:
  SDL_Rect rectangle;
  int center_x, center_y;

  float zoom_level;
  int original_w;
  int original_h;
  
public:
  Camera(int width, int height, SDL_Rect &rect);

  void update(SDL_Rect &rect);

  void zoom(SDL_Renderer* renderer, float zoom);
};

#endif
