#ifndef _LABEL_H
#define _LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
class Label
{
public:
  SDL_Texture* font_texture = NULL;
  int font_size;
  SDL_Rect rectangle;

public:
  Label(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* message, int x, int y);

  void update_texture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* message, int x, int y);

  void render(SDL_Renderer* renderer);
};




#endif
