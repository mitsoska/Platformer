#include "map.hpp"

Map::Map(SDL_Texture* texture, SDL_Texture* gem_texture,int width, int height, int* block_types, int num_blocks_per_row, int total_tiles, TTF_Font* font, int list[7])
{

  this->font = font;
  this->map_texture = texture;
  this->gem_texture = gem_texture;
  this->tile_width = width;
  this->tile_height = height;

  // Calloc is a life-saver. I mistakenly used malloc while also initializing some aspects of the list to 0. Why not use calloc? It's made for this purpose after all.
  
  this->tiles = (Tile*) calloc(total_tiles, sizeof(Tile));
  this->dropped_items = (Item*) calloc(200,sizeof(Item));
  this->trees = (Tree*) calloc(20, sizeof(Tree));
  this->gems = (Gem*) calloc(40, sizeof(Gem));
  this->background_tiles = (Tile*) calloc(total_tiles, sizeof(Tile));
  
  this->total_tiles = total_tiles;
  this->num_blocks_per_row = num_blocks_per_row;
  
  for(int i = 0; i < total_tiles; i++)
    {
      Tile* new_tile = new Tile((i % num_blocks_per_row) * tile_width, tile_height * floor(i / num_blocks_per_row), block_types[i], this->tile_width, this->tile_height, list[block_types[i]]);
     
      // After creating the tile I delete the pointer used to not cause memory problems
      this->tiles[i] = *new_tile;
      delete new_tile;
      new_tile = NULL;
    }

  for(int i = 0; i < total_tiles; i++)
  {
      if(this->tiles[i].index_in_texture != 0)
      {
	  Tile* new_tile = new Tile((i % num_blocks_per_row) * tile_width, tile_height * floor(i / num_blocks_per_row), 7, this->tile_width, this->tile_height, 2);
     
	  // After creating the tile I delete the pointer used to not cause memory problems
	  this->background_tiles[i] = *new_tile;
	  delete new_tile;
	  new_tile = NULL;

      }

  }
  
}

void Map::kill_item(int i)
{
  

  // First I de-activate the correpsonding element
  this->dropped_items[i].id = 0;


  // Then if it's not at the end of the list, I replace its value with the value of the last item while also deactivting the last item.
  
  if(i != this->blocks_dropped - 1)
    {
      this->dropped_items[i] = this->dropped_items[this->blocks_dropped - 1];
      this->dropped_items[this->blocks_dropped - 1].id = 0;
    }
  
  blocks_dropped -= 1;
    
	
}

void Map::drop_item(int id, int quantity, int x, int y, SDL_Texture* background_texture, int prob, int seed_prob, SDL_Renderer* renderer, Camera &camera)
{
  //Transforming grass-dirt to dirt
  if (id == 3) { id = 1;}

  if (prob == 1)
    {
      this->blocks_dropped += 1;
  
      for(int i = 0; i < this->blocks_dropped; i++)
	{
	  if(this->dropped_items[i].id == 0)
	    {
	      // Again, deleting the pointer to avoid memeory issues
	      
	      Item* item_pointer = new Item(id, quantity, x / camera.zoom_level, y / camera.zoom_level, background_texture, this->map_texture, this->font, renderer, camera);
	      this->dropped_items[i] = *item_pointer;
	      delete item_pointer;

	      // Avoiding dangling pointers
	      item_pointer = NULL;
	    
	      break;

	    }


	}
    }

  if(seed_prob == 1)
    {
      this->blocks_dropped += 1;
  
      for(int i = 0; i < this->blocks_dropped; i++)
	{
	  if(this->dropped_items[i].id == 0)
	    {
	      // 4 is the stride between seeds and blocks

	      Item* item_pointer = new Item(id + 7, quantity, (x + 10) / camera.zoom_level, y / camera.zoom_level, background_texture, this->map_texture, this->font, renderer, camera);
	      this->dropped_items[i] = *item_pointer;
	      delete item_pointer;

	      // Avoiding dangling pointers
	      item_pointer = NULL;
	    
	      break;

	    }


	}




    }
}



void Map::drop_gem(int x, int y, int type)
{

  for(int i = 0; i < 40; i++)
    if(this->gems[i].type == 0)
      {

	Gem* gem_pointer = new Gem(type, x, y, this->gem_texture);
	this->gems[i] = *gem_pointer;
	delete gem_pointer;

	// Avoiding dangling pointers
	gem_pointer = NULL;
	    
	break;



      }


}

void Map::collect_gems(SDL_Renderer* renderer, SDL_Rect &play_rect, GemDisplay &gem_disp)
{
  for(int i = 0; i < 40; i++)
    {
      if(this->gems[i].type != 0 && play_rect.x + play_rect.w > this->gems[i].rectangle.x && play_rect.x  < this->gems[i].rectangle.x + this->gems[i].rectangle.w && play_rect.y + play_rect.h > this->gems[i].rectangle.y && play_rect.y  < this->gems[i].rectangle.y + this->gems[i].rectangle.h)
	{
	  this->gems[i].type = 0;
	  gem_disp.value += 1;
	  gem_disp.update_texture(renderer);
	  break;
	
	}
    }
}


void Map::break_tree(int index, int id, SDL_Texture* background_texture, int prob, int seed_prob, SDL_Renderer* renderer, Camera &camera)
{

  this->trees[index].id = 0;
  
  this->drop_item(id - 14, 3, this->trees[index].rectangle.x + this->trees[index].rectangle.w / 2, this->trees[index].rectangle.y - 15, background_texture, prob, seed_prob, renderer, camera);

}

void Map::render(SDL_Renderer* renderer, Camera &camera, SDL_Rect &player)
{
  
  for(int i = 0; i < total_tiles; i++)
    {

      // Changing the ids of some tiles in order for the tilemap to be completely correct
      
      if(this->tiles[i].index_in_texture == 1 && this->tiles[i - num_blocks_per_row].index_in_texture == 0)
	this->tiles[i].index_in_texture = 3;

      if(this->tiles[i].index_in_texture == 3 && (this->tiles[i - num_blocks_per_row].index_in_texture == 3 || this->tiles[i - num_blocks_per_row].index_in_texture == 1))
	this->tiles[i].index_in_texture = 1;

    }

  for(int i = 0; i < this->total_tiles; i++)
  {

      SDL_Rect rect = {this->tile_width * this->background_tiles[i].index_in_texture, 0, this->tile_width, this->tile_height};

      // Using a drawing rect so I can transform the tile according to the camera

      SDL_Rect drawrect = {this->background_tiles[i].rectangle.x - camera.rectangle.x , this->background_tiles[i].rectangle.y - camera.rectangle.y, this->background_tiles[i].rectangle.w, this->background_tiles[i].rectangle.h};
            
      SDL_RenderCopy(renderer, this->map_texture, &rect , &drawrect);

  }

  for(int i = 0; i < this->total_tiles; i++)
    {

      SDL_Rect rect = {this->tile_width * this->tiles[i].index_in_texture, 0, this->tile_width, this->tile_height};

      // Using a drawing rect so I can transform the tile according to the camera

      SDL_Rect drawrect = {this->tiles[i].rectangle.x - camera.rectangle.x , this->tiles[i].rectangle.y - camera.rectangle.y, this->tiles[i].rectangle.w, this->tiles[i].rectangle.h};
            
      SDL_RenderCopy(renderer, this->map_texture, &rect , &drawrect);


      // Rect is being automatically destroyed by SDL, so no memory worries here.
    }

  for(int i = 0; i < this->blocks_dropped; i++)
    {
      if(this->dropped_items[i].id != 0)
	  this->dropped_items[i].render(renderer, camera);
    }

  for(int i = 0; i < 20; i++)
    {

      if(this->trees[i].id != 0)
	{
	  this->trees[i].render(renderer, camera, player);
	}
    }

  for(int i = 0; i < 40; i++)
    {
      if(this->gems[i].type != 0)
	this->gems[i].render(renderer, camera);


    }
}

int Map::get_block(SDL_Rect &rect)
{
  // returns the index of the block that the player is located at

  for(int i = 0; i < this->total_tiles; i++)
    {
      if((abs(rect.y - this->tiles[i].rectangle.y) < this->tile_height && this->tiles[i].rectangle.y + this->tiles[i].rectangle.h - rect.y > this->tile_width - (this->tiles[i + this->num_blocks_per_row].rectangle.y + this->tiles[i + this->num_blocks_per_row].rectangle.h - rect.y - rect.h)) && (rect.x - this->tiles[i].rectangle.x < this->tile_width && this->tiles[i].rectangle.x + this->tiles[i].rectangle.w - rect.x > rect.w + rect.x - this->tiles[i + 1].rectangle.x))
	{
	  return i;
	  continue;
	}
    }

  return -1;
}

int Map::get_block_by_pos(int x, int y, Camera &camera)
{

  // Returns the index of the block which contains the x and y values given
  for(int i = 0; i < this->total_tiles; i++)
    {
      if( x / camera.zoom_level >= this->tiles[i].rectangle.x - camera.rectangle.x && x / camera.zoom_level<= this->tiles[i].rectangle.x + this->tiles[i].rectangle.w - camera.rectangle.x && y / camera.zoom_level >= this->tiles[i].rectangle.y - camera.rectangle.y && y / camera.zoom_level <= this->tiles[i].rectangle.y + this->tiles[i].rectangle.h - camera.rectangle.y)
	return i;
      

    }

  return -1;
}


int Map::get_tree_by_pos(int x, int y, Camera &camera)
{
 
  for(int i = 0; i < 20; i++)
    {
      if(this->trees[i].id != 0  && x / camera.zoom_level >= this->trees[i].rectangle.x - camera.rectangle.x && x / camera.zoom_level <= this->trees[i].rectangle.x + this->trees[i].rectangle.w - camera.rectangle.x && y / camera.zoom_level > this->trees[i].rectangle.y - 32 - camera.rectangle.y  && y / camera.zoom_level < this->trees[i].rectangle.y - camera.rectangle.y)
	{

	  return i;
        
	}
    }
  
  return -1;
  
}
int Map::get_type(int index)
{
  
  return this->tiles[index].index_in_texture;

}
