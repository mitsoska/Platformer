#ifndef _GEM_DISPLAY_
#define _GEM_DISPLAY_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>

class GemDisplay
{
public:
  SDL_Texture* texture;
  SDL_Texture* font_text;

  SDL_Rect main_rect;
  SDL_Rect font_rect;
  
  TTF_Font* font;
  std::string string_value;

  int value;
  int original_x;
  
public:
  GemDisplay(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture, TTF_Font* font);

  void update_texture(SDL_Renderer* renderer);

  void render(SDL_Renderer* renderer);
};


#endif
