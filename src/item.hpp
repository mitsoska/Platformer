#ifndef _ITEM_H
#define _ITEM_H

#include "sound.hpp"
#include <SDL2/SDL.h>
#include "camera.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>

class Item
{

public:
  int id;
  SDL_Rect item_rect;
  SDL_Rect font_rect;

  SDL_Texture* block_texture;
  SDL_Texture* background_texture;
  SDL_Texture* quantity_texture;
  
  TTF_Font* font;

  std::string text_quantity;
  
  int quantity;

  int y;
  
public:

  Item(int id, int quantity, int x, int y, SDL_Texture* background_texture, SDL_Texture* block_texture, TTF_Font* font, SDL_Renderer* renderer, Camera &camera);
    
  void render(SDL_Renderer* renderer, Camera &camera);


};



#endif
