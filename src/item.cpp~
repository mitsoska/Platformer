#include "item.hpp"

Item::Item(int id, int quantity, int x, int y, SDL_Texture* background_texture, SDL_Texture* block_texture, TTF_Font* font, SDL_Renderer* renderer, Camera &camera)
{

  this->id = id;
  this->quantity = quantity;
  this->item_rect.x = x;
  this->item_rect.y = y; 
  this->background_texture = background_texture;
  this->block_texture = block_texture;

  // Y will be useful in the rendering process
  this->y = y;
  
  SDL_QueryTexture(this->background_texture, NULL, NULL, &this->item_rect.w, &this->item_rect.h);
  
  this->text_quantity = std::to_string(this->quantity);

  SDL_Color color = {255,255,255};
  
  this->font_rect.x = this->item_rect.x + 16;
  this->font_rect.y = this->item_rect.y + + this->item_rect.h - 10;
  
  SDL_Surface* surface = TTF_RenderText_Solid(font, this->text_quantity.c_str(), color);
 
  this->quantity_texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  this->font_rect.w = surface->w;
  this->font_rect.h = surface->h;

  SDL_FreeSurface(surface);

  
  
}

void Item::render(SDL_Renderer* renderer, Camera &camera)
{

  if(this->id != 0)
    {
      this->item_rect.x -= 5;
      this->item_rect.y = this->y + 10 * sin(SDL_GetTicks() / 200.0f);
      
      SDL_QueryTexture(this->background_texture, NULL, NULL, &this->item_rect.w, &this->item_rect.h);

      
      this->font_rect.x = this->item_rect.x + 16 - camera.rectangle.x;
      this->font_rect.y = this->item_rect.y +  this->item_rect.h - 15 - camera.rectangle.y;

      
      SDL_Rect drawing_rect = {this->item_rect.x - camera.rectangle.x,this->item_rect.y - camera.rectangle.y, this->item_rect.w, this->item_rect.h};

      SDL_RenderCopy(renderer, this->background_texture, NULL, &drawing_rect);

      this->item_rect.x += 5;
      this->item_rect.y += 5;
      this->item_rect.w /= 2;
      this->item_rect.h /= 2;
  
      SDL_Rect texture_rect = {32 * this->id, 0, 32, 32};
      SDL_Rect drawing_rect2 = {this->item_rect.x - camera.rectangle.x, this->item_rect.y - camera.rectangle.y, this->item_rect.w, this->item_rect.h};
      
      SDL_RenderCopy(renderer, this->block_texture, &texture_rect, &drawing_rect2);

      
      SDL_RenderCopy(renderer, this->quantity_texture, NULL, &this->font_rect);

    }

}
