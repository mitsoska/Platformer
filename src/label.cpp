#include <cassert>
#include "label.hpp"
#include <iostream>

Label::Label(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* message, int x, int y)
{
  SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
 
  this->font_texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->rectangle.w = surface->w;
  this->rectangle.h = surface->h;
  this->rectangle.x = x;
  this->rectangle.y = y;

  SDL_FreeSurface(surface);
}

void Label::update_texture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* message, int x, int y)
{

  SDL_DestroyTexture(this->font_texture);


  SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
 
  this->font_texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->rectangle.w = surface->w;
  this->rectangle.h = surface->h;
  this->rectangle.x = x;
  this->rectangle.y = y;

  SDL_FreeSurface(surface);
}

void Label::render(SDL_Renderer* renderer)
{
  SDL_RenderCopy(renderer, this->font_texture, NULL,  &this->rectangle);
}
/*sddasdpasa      _________________
/SAssaQCXL       /                 |
0 || 0 s-|      /  MEOW! Uwu       |
 [  ]  |/      /  |----------------|
------ |      /___|
\ ~~  /
|\___/|
|  .  |\______
              \
   |       /   \
   |      /    |\
---|------ |     |
           |
*/
