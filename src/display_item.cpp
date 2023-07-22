#include "display_item.hpp"


DisplayItem::DisplayItem(SDL_Renderer* renderer, int id, int quantity, SDL_Texture* texture, TTF_Font* font, int x, int y, SDL_Color& color, const char* titles[12], Camera &camera)  : title_clock(2000.0f)
{

  this->font = font;

  this->is_selected = false;
  this->rectangle = {x, y};
  this->id = id;
  this->quantity = quantity;
  this->background_texture = texture;
   
  
  SDL_QueryTexture(this->background_texture, NULL, NULL, &this->rectangle.w, &this->rectangle.h);

  this->original = {x, y, this->rectangle.w + 15, this->rectangle.h + 15};

  this->rectangle.w /= camera.zoom_level;
  this->rectangle.h /= camera.zoom_level;
  
  this->rectangle.w += 15 / camera.zoom_level;
  this->rectangle.h += 15 / camera.zoom_level;

  this->string_quantity = std::to_string(this->quantity);
  
  
  SDL_Surface* surface = TTF_RenderText_Solid(font, this->string_quantity.c_str(), color);
 
  this->quantity_texture = SDL_CreateTextureFromSurface(renderer, surface);

  this->original_text_w = surface->w;
  this->original_text_h = surface->h;
  
  this->quantity_rect.w = surface->w / camera.zoom_level;
  this->quantity_rect.h = surface->h / camera.zoom_level;

  this->quantity_rect.x = this->rectangle.x + this->rectangle.w - this->quantity_rect.w - 5;
  this->quantity_rect.y = this->rectangle.y + this->rectangle.h - this->quantity_rect.h / camera.zoom_level;
  
  SDL_FreeSurface(surface);

  SDL_Surface* surface2 = TTF_RenderText_Solid(font, titles[id - 1], color);
  this->title_texture = SDL_CreateTextureFromSurface(renderer, surface2);

  SDL_FreeSurface(surface2);

}


void DisplayItem::render(SDL_Renderer* renderer, Map& map, Camera &camera)
{


  // For the background
  SDL_RenderCopy(renderer, this->background_texture, NULL, &this->rectangle);

  // For the item image
  this->rectangle.x += this->rectangle.w / 2 - int(10 / camera.zoom_level);
  this->rectangle.y += this->rectangle.h / 2 - int(10 / camera.zoom_level);
  this->rectangle.w /= 2.5;// * camera.zoom_level;
  this->rectangle.h /= 2.5;// * camera.zoom_level;
  
  SDL_Rect texture_rect = {32 * this->id, 0, 32, 32};

  SDL_RenderCopy(renderer, map.map_texture, &texture_rect,  &this->rectangle);

  SDL_RenderCopy(renderer, this->quantity_texture, NULL, &this->quantity_rect);

  this->rectangle.w *= 2.5;// * camera.zoom_level;
  this->rectangle.h *= 2.5;// * camera.zoom_level;
    
  this->rectangle.x -= this->rectangle.w / 2 - int(10 / camera.zoom_level);
  this->rectangle.y -= this->rectangle.h / 2 - int(10 / camera.zoom_level);

  if(is_selected && title_clock.is_running())
    {

      SDL_Rect back = {this->rectangle.x - 15 / camera.zoom_level, this->rectangle.y - 35 / camera.zoom_level, this->rectangle.w + 25 / camera.zoom_level , this->rectangle.h - 15 / camera.zoom_level};

      SDL_SetRenderDrawColor(renderer, 20, 20, 10, 255);
      SDL_RenderFillRect(renderer, &back);

      
      SDL_Rect title_rect = {this->rectangle.x - 10 / camera.zoom_level, back.y + 5 / camera.zoom_level, back.w - 5 / camera.zoom_level, back.h - 10 / camera.zoom_level};
      SDL_RenderCopy(renderer, this->title_texture, NULL, &title_rect);


    }
}

void DisplayItem::update_texture(SDL_Renderer* renderer)
{
  
  SDL_DestroyTexture(this->quantity_texture);

  this->string_quantity = std::to_string(this->quantity);

  SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->string_quantity.c_str(), this->white);
 
  this->quantity_texture = SDL_CreateTextureFromSurface(renderer, surface);

  this->quantity_rect.w = surface->w;
  this->quantity_rect.h = surface->h;

  
  this->quantity_rect.x = this->rectangle.x + this->rectangle.w - this->quantity_rect.w - 5;
  this->quantity_rect.y = this->rectangle.y + this->rectangle.h - this->quantity_rect.h;

  SDL_FreeSurface(surface);

  
    
}

bool DisplayItem::is_hover(Camera &camera)
{
  int x, y;
  SDL_GetMouseState(&x, &y);
  
  return ((x / camera.zoom_level < this->rectangle.x + this->rectangle.w && x / camera.zoom_level > this->rectangle.x) && (y  / camera.zoom_level < this->rectangle.y + this->rectangle.h && y/ camera.zoom_level > this->rectangle.y));

}

