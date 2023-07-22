#include "gem.hpp"

Gem::Gem(int type, int x, int y, SDL_Texture* texture)
{
  this->type = type;

  this->rectangle.x = x;
  this->rectangle.y = y;
  this->texture = texture;

  this->y = y;
}

void Gem::render(SDL_Renderer* renderer, Camera &camera)
{

  this->rectangle.y = this->y + 10 * sin(SDL_GetTicks() / 200.0f);

  SDL_Rect texture_rect = {16 * this->type, 0, 16, 16};

  SDL_Rect draw_rect = {this->rectangle.x - camera.rectangle.x, this->rectangle.y - camera.rectangle.y, 16, 16};

  SDL_RenderCopy(renderer, this->texture, &texture_rect, &draw_rect);
  
}
