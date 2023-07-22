#include "camera.hpp"


Camera::Camera(int width, int height, SDL_Rect &rect)
{
  this->rectangle.w = width;
  this->rectangle.h = height;

  this->original_w = width;
  this->original_h = height;
  
  this->rectangle.x = rect.x + rect.w / 2 - this->rectangle.w / 2;
  this->rectangle.y = rect.y + rect.h / 2 - this->rectangle.h / 2;

    
  if(this->rectangle.x < 0)
    this->rectangle.x = 0;

  if(this->rectangle.y < 0)
    this->rectangle.y = 0;
}


void Camera::update(SDL_Rect &rect)
{
 
  
  this->rectangle.x = rect.x + rect.w / 2 - this->rectangle.w / 2;
  this->rectangle.y = rect.y + rect.h / 2 - this->rectangle.h / 2;

  
}

void Camera::zoom(SDL_Renderer* renderer, float zoom_value)
{

  SDL_RenderSetScale(renderer, zoom_value, zoom_value);

  this->zoom_level = zoom_value;

  this->rectangle.w = int(original_w / zoom_value);
  this->rectangle.h = int(original_h / zoom_value);
    
}
