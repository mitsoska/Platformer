#include "sprite.hpp"
#include <SDL2/SDL_image.h>

// Sprite Class: A textured rectangle

Sprite::Sprite( SDL_Renderer* renderer, const char* texture_path, int x, int y)
{

  this->original_path = texture_path;
  this->texture = IMG_LoadTexture(renderer, texture_path);

  // I made the texture and now I am changing the rectangle's dimension in order for them to fit the newly created SDL_Texture
  SDL_QueryTexture(this->texture, NULL, NULL, &this->rectangle.w, &this->rectangle.h);


  this->rectangle.x = x;
  this->rectangle.y = y;
  
}


void Sprite::scale(float scalar)
{

  this->rectangle.w *= scalar;
  this->rectangle.h *= scalar;
  
}


bool Sprite::is_hover()
{
  int mouse_x, mouse_y;

  SDL_GetMouseState(&mouse_x, &mouse_y);

  return (mouse_x >= this->rectangle.x && mouse_x <= this->rectangle.w + this->rectangle.x) && (mouse_y >= this->rectangle.y && mouse_y <= this->rectangle.y + this->rectangle.h);
}



void Sprite::render(SDL_Renderer* renderer, Camera &camera, bool &is_looking_right)
{

  SDL_Rect drawing_rect = {this->rectangle.x - camera.rectangle.x, this->rectangle.y - camera.rectangle.y, this->rectangle.w, this->rectangle.h};
  
  if(is_looking_right)
  {
      SDL_RenderCopyEx(renderer, this->texture, NULL, &drawing_rect, NULL, NULL, SDL_FLIP_NONE);
  } else {SDL_RenderCopyEx(renderer, this->texture, NULL, &drawing_rect, NULL, NULL, SDL_FLIP_HORIZONTAL);}
}

void Sprite::apply_collisions(float& speed, Map& new_map, bool &is_jumping)
{

  if((new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].index_in_texture == 0 && this->rectangle.y + this->rectangle.h  >= new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].rectangle.y) || (new_map.tiles[new_map.get_block(this->rectangle)].index_in_texture == 0 && this->rectangle.y + this->rectangle.h <= new_map.tiles[new_map.get_block(this->rectangle)].rectangle.y + new_map.tiles[new_map.get_block(this->rectangle)].rectangle.h))
    {
      speed += 15.0 * 1.0 / 60;
     
      this->rectangle.y += int(speed);

    } else {this->rectangle.y += int(speed);}

  
  if(this->rectangle.y + this->rectangle.h > new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].rectangle.y && new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].index_in_texture != 0 && this->rectangle.y + this->rectangle.h != new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].rectangle.y)
	{
	  this->rectangle.y = new_map.tiles[new_map.get_block(this->rectangle) + new_map.num_blocks_per_row].rectangle.y - this->rectangle.h;
	  //this->rectangle.y -= int(speed);
	  speed = 0.0f;
	  is_jumping = false;
	}

  if(this->rectangle.y <= new_map.tiles[new_map.get_block(this->rectangle) - new_map.num_blocks_per_row].rectangle.y + new_map.tiles[new_map.get_block(this->rectangle) - new_map.num_blocks_per_row].rectangle.h && new_map.tiles[new_map.get_block(this->rectangle) - new_map.num_blocks_per_row].index_in_texture != 0)
    {
      this->rectangle.y = new_map.tiles[new_map.get_block(this->rectangle) - new_map.num_blocks_per_row].rectangle.y + new_map.tiles[new_map.get_block(this->rectangle) - new_map.num_blocks_per_row].rectangle.h; 
      speed += 15.0 * 1.0/ 60;


    }

}

void Sprite::move(int& speed, direction dir, Map &map)
{

  this->rectangle.x += dir * int(speed / 60.0f);

  
  if(
     ( map.tiles[map.get_block(this->rectangle) + 1].index_in_texture != 0 && this->rectangle.x + this->rectangle.w >= map.tiles[map.get_block(this->rectangle) + 1].rectangle.x && dir == RIGHT && this->rectangle.x < map.tile_width * map.num_blocks_per_row - this->rectangle.w)
     ||

     (map.tiles[map.get_block(this->rectangle)].index_in_texture != 0 && this->rectangle.x + this->rectangle.w > map.tiles[map.get_block(this->rectangle)].rectangle.x)

     // // Bottom right block
     // (map.tiles[map.get_block(this->rectangle) + 1 + map.num_blocks_per_row].index_in_texture != 0 && this->rectangle.x + this->rectangle.w >= map.tiles[map.get_block(this->rectangle) + 1 + map.num_blocks_per_row].rectangle.x && dir == RIGHT && this->rectangle.y + this->rectangle.h != map.tiles[map.get_block(this->rectangle) + 1 + map.num_blocks_per_row].rectangle.y && this->rectangle.x < map.tile_width * map.num_blocks_per_row - map.tile_width) 

     ||

     // Upper right block

     (map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row + 1].index_in_texture != 0 && this->rectangle.x + this->rectangle.w >= map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row + 1].rectangle.x && dir == RIGHT && this->rectangle.y + this->rectangle.h != map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row + 1].rectangle.y && this->rectangle.y < map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row + 1].rectangle.y + map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row + 1].rectangle.h && this->rectangle.x < map.tile_width * map.num_blocks_per_row - map.tile_width)
     

    ||

    //Upper block
    (map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row].index_in_texture != 0 && this->rectangle.x + this->rectangle.w >= map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row].rectangle.x && dir == RIGHT && this->rectangle.y < map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row].rectangle.y + map.tiles[map.get_block(this->rectangle) - map.num_blocks_per_row].rectangle.h && this->rectangle.x < map.tile_width * map.num_blocks_per_row - map.tile_width)
      )

    {
      this->rectangle.x -= dir * int(speed / 60.0f);
      speed = 0;
    }

  if(
     // Left block
     (map.tiles[map.get_block(this->rectangle) - 1].index_in_texture != 0 && this->rectangle.x <= map.tiles[map.get_block(this->rectangle) - 1].rectangle.x + map.tiles[map.get_block(this->rectangle) - 1].rectangle.w && map.tiles[map.get_block(this->rectangle)].index_in_texture == 0 && dir == LEFT && this->rectangle.x > this->rectangle.w + map.tile_width / 2) //|| 

     // // Buttom left block
     // (map.tiles[map.get_block(this->rectangle) -1 + map.num_blocks_per_row].index_in_texture != 0 && this->rectangle.x <= map.tiles[map.get_block(this->rectangle) - 1 + map.num_blocks_per_row].rectangle.x + map.tiles[map.get_block(this->rectangle) - 1 + map.num_blocks_per_row].rectangle.w && dir == LEFT && this->rectangle.y + this->rectangle.h != map.tiles[map.get_block(this->rectangle) - 1 + map.num_blocks_per_row].rectangle.y && this->rectangle.x > this->rectangle.w + map.tile_width / 2)
     )
    {
      this->rectangle.x -= dir * int(speed / 60.0f);
      speed = 0;
    }
}
