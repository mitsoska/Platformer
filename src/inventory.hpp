#ifndef _INVENTORY_
#define _INVENTORY_

#include "item.hpp"
#include <cstdlib>
#include <list>
#include "display_item.hpp"
#include "map.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "camera.hpp"

class Inventory
{
public:
  int slots;

  SDL_Rect main_rect;

  //To realloc again every time user buys inventory upgrade
  DisplayItem* items;
  
  SDL_Texture* background_texture;
  SDL_Texture* button_texture;
  SDL_Texture* button_texture_hover;

  TTF_Font* font;

  
public:
  Inventory(int slots, SDL_Texture* main_texture, SDL_Texture* button_texture, SDL_Texture* button_texture_on_hover, TTF_Font* font, Camera &camera);

    
  void check_collect_item(SDL_Renderer* renderer, SDL_Rect& player, Map& map, const char* titles[12], Camera &camera);

  void update(Camera& camera);

  void update_drag(Camera &camera);
  
  void place_item(SDL_Renderer* renderer, DisplayItem &item, int x, int y, Map &map, Camera &camera, int list[2][3]);
  
  void render(SDL_Renderer* renderer, Map& map, Camera &camera);
  
};


#endif
