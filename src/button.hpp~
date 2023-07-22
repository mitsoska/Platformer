#ifndef _BUTTON_H
#define _BUTTON_H

#include "sprite.hpp"
#include "label.hpp"

class Button
{

public:
  Sprite icon, background;

  Label title;

  SDL_Rect descr_rect;
  SDL_Texture *descr_texture;

  int price;
  float cps;

public:
  Button(SDL_Renderer* renderer, Label &title, TTF_Font* font, const char* description, SDL_Color color, Sprite &icon, Sprite &background, int price, float cps, int x, int y);

  void render(SDL_Renderer* renderer, const char* hover_path);

  bool is_hover();

};

#endif
