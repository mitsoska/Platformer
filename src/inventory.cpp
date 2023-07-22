#include "inventory.hpp"

Inventory::Inventory(int slots, SDL_Texture* main_texture, SDL_Texture* button_texture, SDL_Texture* hover_texture, TTF_Font* font, Camera &camera)
{

  // Calloc initializes the bytes to 0 automatically!!!
  this->items = (DisplayItem*) calloc(slots, sizeof(DisplayItem));

  this->background_texture = main_texture;
  this->button_texture = button_texture;
  this->button_texture_hover = hover_texture;
  this->main_rect = {400 - 150, 800 - 70, 300, 70 * ceil(slots / 5.0)};  
  this->slots = slots;
  this->font = font;
  
}

void Inventory::check_collect_item(SDL_Renderer* renderer, SDL_Rect& player, Map& map, const char* titles[12], Camera &camera)
{

  for(int i = 0; i < map.blocks_dropped; i ++)
    {

        
      if(map.dropped_items[i].id != 0 && abs(map.dropped_items[i].item_rect.x + map.dropped_items[i].item_rect.w / 2 - player.x - player.w / 2) < player.w / 2 + map.dropped_items[i].item_rect.w / 2 && abs(map.dropped_items[i].item_rect.y + map.dropped_items[i].item_rect.h / 2 - player.y - player.h / 2) < player.h / 2 + map.dropped_items[i].item_rect.h / 2)
	{
	 
	  bool is_in_list = false;
	  
	  for(int k = 0; k < this->slots; k++)
	    {
	      
	      if(this->items[k].id == map.dropped_items[i].id  && this->items[k].id != 0)
		{
		  this->items[k].quantity += map.dropped_items[i].quantity;
		  this->items[k].update_texture(renderer);

		  is_in_list = true;
		  map.kill_item(i);

		  break;

		}
	    }
	  
	  for(int k = 0; k < this->slots; k++)
	    {
	  
	      if(!is_in_list && this->items[k].id == 0)
		{

		  SDL_Color white = {255,255,255};

		  DisplayItem *pointer = new DisplayItem(renderer, map.dropped_items[i].id, map.dropped_items[i].quantity, this->button_texture, this->font, this->main_rect.x + int((25 + (k % 5) * 50) / camera.zoom_level), this->main_rect.y + (20 + floor(k / 5) * 50) / camera.zoom_level, white, titles, camera);

		  this->items[k] = *pointer;

		  delete pointer;
		  pointer = NULL;

		  map.kill_item(i);

		  break;


		}
	    }	  
	     

	   

	 
	}

    }
}

void Inventory::place_item(SDL_Renderer* renderer, DisplayItem &item ,int x, int y, Map &map, Camera &camera, int  my_list[2][3])
{
  if(item.id != 0 && item.id <= 7 && map.tiles[map.get_block_by_pos(x,y,camera)].index_in_texture == 0)
    {
      item.quantity -= 1;
      map.tiles[map.get_block_by_pos(x, y, camera)].index_in_texture = item.id;

      if(item.quantity == 0)
	{
	  item.id = 0;
	  item.is_selected = false;
	}

	item.update_texture(renderer);

    }

  if(item.id > 7 && map.tiles[map.get_block_by_pos(x, y, camera)].index_in_texture == 0 && item.quantity >= 1 && map.tiles[map.get_block_by_pos(x , y, camera) + map.num_blocks_per_row].index_in_texture != 0 && map.trees[map.get_tree_by_pos(x, y, camera)].id == 0)
    {
      item.quantity -= 1;
      
      Tree *pointer = new Tree(renderer, this->font, map.tiles[map.get_block_by_pos(x, y, camera)].rectangle.x, map.tiles[map.get_block_by_pos(x, y, camera)].rectangle.y + 32, map.map_texture , item.id + 7);

            
      for(int i = 0; i < 20; i ++)
	{
	  if(map.trees[i].id == 0)
	    {
	      map.trees[i] = *pointer;
	      break;
	    }

	}

      if(item.quantity == 0)
	{
	  item.id = 0;
	  item.is_selected = false;

	}

      item.update_texture(renderer);
      delete pointer;
      pointer = NULL;
  

    }

  if(item.id > 7 && map.trees[map.get_tree_by_pos(x, y, camera)].id >= 14 && item.quantity >= 1 && item.id != map.trees[map.get_tree_by_pos(x, y, camera)].id - 7)
    {
      for(int i = 0; i < 5; i++)
	{
	  if((my_list[i][0] == item.id || my_list[i][1] == item.id) && (my_list[i][0] == map.trees[map.get_tree_by_pos(x, y, camera)].id - 7 || my_list[i][1] == map.trees[map.get_tree_by_pos(x, y, camera)].id) - 7)
	    {
	      	      
	      item.quantity -= 1;

	      Tree *pointer = new Tree(renderer, this->font, map.tiles[map.get_block_by_pos(x, y, camera)].rectangle.x, map.tiles[map.get_block_by_pos(x, y, camera)].rectangle.y + 32, map.map_texture , my_list[i][2]);

	      
	      map.trees[(map.get_tree_by_pos(x, y, camera))] = *pointer;

	      delete pointer;
	      pointer = NULL;

      
	      if(item.quantity == 0)
		{
		  item.id = 0;
		  item.is_selected = false;

		}

	      item.update_texture(renderer);

	      break;
	    }
	}

    }

}

void Inventory::update(Camera &camera)
{

  this->main_rect = {int((400 - 150) / camera.zoom_level), int((800 - 70) / camera.zoom_level), int(300 / camera.zoom_level), int(70 / camera.zoom_level)}; 

  for(int i =0; i < this->slots; i++)
    {
      this->items[i].rectangle.w = this->items[i].original.w / camera.zoom_level;
      this->items[i].rectangle.h = this->items[i].original.h / camera.zoom_level;;
      this->items[i].rectangle.x = this->main_rect.x + int((25 + (i % 5) * 50) / camera.zoom_level);
      this->items[i].rectangle.y = this->main_rect.y + int((20 + (floor(i / 5.0) * 50)) / camera.zoom_level);

      this->items[i].quantity_rect.x = this->items[i].rectangle.x  + 3/2 * this->items[i].rectangle.w ;
      this->items[i].quantity_rect.y = this->items[i].rectangle.y  + this->items[i].rectangle.h - 10 / camera.zoom_level;
      this->items[i].quantity_rect.w = this->items[i].original_text_w / camera.zoom_level;
      this->items[i].quantity_rect.h = this->items[i].original_text_h / camera.zoom_level;
    }
  
}

void Inventory::update_drag(Camera &camera)
{

  for(int i = 0; i < this->slots; i++)
    {
	this->items[i].rectangle.y = this->main_rect.y + int((20 + (floor(i / 5.0) * 50)) / camera.zoom_level);

  this->items[i].quantity_rect.y = this->items[i].rectangle.y + this->items[i].rectangle.h - this->items[i].quantity_rect.h;
  


    }

}

void Inventory::render(SDL_Renderer* renderer, Map& map, Camera &camera)
{

  SDL_RenderCopy(renderer, this->background_texture, NULL, &this->main_rect);
  
  for(int i = 0; i < this->slots; i++)
    {
     
      if(this->items[i].id == 0)
	{

	  SDL_Rect empty = {this->main_rect.x + int((25 + (i % 5) * 50) / camera.zoom_level), this->main_rect.y + int((20 + (floor(i / 5) * 50)) / camera.zoom_level)};

	  SDL_QueryTexture(this->button_texture, NULL, NULL, &empty.w, &empty.h);

	  empty.w = empty.w / camera.zoom_level;
	  empty.h = empty.h / camera.zoom_level;
	  
	  empty.w += 15 / camera.zoom_level;
	  empty.h += 15 / camera.zoom_level;
	  
	  SDL_RenderCopy(renderer, this->button_texture, NULL, &empty);

	} else {

      
	if(!this->items[i].is_selected)
	  {
	    this->items[i].background_texture = this->button_texture;
	  } else {this->items[i].background_texture = this->button_texture_hover;}

	this->items[i].render(renderer, map, camera);


      }
      
    }

}
