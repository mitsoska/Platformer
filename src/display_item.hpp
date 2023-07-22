#ifndef _DISPLAY_ITEM_
#define _DISPLAY_ITEM_

#include "label.hpp"
#include <SDL2/SDL.h>
#include <string>
#include "map.hpp"
#include "camera.hpp"

class DisplayItem
{
public:

  SDL_Rect original;
  SDL_Rect rectangle;
  SDL_Rect quantity_rect;
  
  SDL_Texture* background_texture;
  SDL_Texture* quantity_texture;
  SDL_Texture* title_texture;
  
  std::string* titles;

  int original_text_w, original_text_h;
  TTF_Font* font;
  
  int id;
  int quantity;

  bool is_selected = false;

  Timer title_clock;
  
  std::string string_quantity;

  SDL_Color white = {255,255,255};

public:

  DisplayItem(SDL_Renderer* renderer, int id, int quantity, SDL_Texture* background_texture, TTF_Font* font, int x, int y, SDL_Color& color, const char* titles[12], Camera& camera);

  void render(SDL_Renderer* renderer, Map& map, Camera &camera);

  void update_texture(SDL_Renderer* renderer);

  bool is_hover(Camera &camera);
};




#endif
