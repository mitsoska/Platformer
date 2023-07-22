#ifndef _TREE_
#define _TREE_


#include "timer.hpp"
#include "camera.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>


class Tree
{
public:
  int growth_time;
  int id;

  int max_drop_blocks;
  int seed_prob;

  int initial_y;
  
  SDL_Rect rectangle;
  SDL_Rect font_rect;

  SDL_Texture* texture;
  SDL_Texture* font_text;
  
  Timer clock;

  TTF_Font* font;
  std::string time_string;

  SDL_Color white = {255, 255, 255};
  
  float growth_times[2];

public:

  Tree(SDL_Renderer* renderer, TTF_Font* font, int x, int y, SDL_Texture* texture, int id);

  void update_texture(SDL_Renderer* renderer);
  
  void render(SDL_Renderer* renderer, Camera &camera, SDL_Rect &player);

};

#endif
