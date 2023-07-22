#include "particle_generator.hpp"
#include <cstdlib>

ParticleGenerator::ParticleGenerator(SDL_Renderer* renderer, float x, float y, int num_of_particles, const char* texture_path, float lifespan, int width, int height)
{
  this->texture = IMG_LoadTexture(renderer, texture_path);
  this->particle_rect.w = width;
  this->particle_rect.h = height;
  this->num_of_particles = num_of_particles;
  this->lifespan = lifespan;

  
  this->particles = (Particle*) malloc(sizeof(Particle) * num_of_particles);
  
  this->move(x, y);
}

void ParticleGenerator::move(float x, float y)
{
  for (int i = 0; i < this->num_of_particles; i++)
    {
      particles[i].respawn(x, y);

      this->origin_x = x;
      this->origin_y = y;
    }
}

void ParticleGenerator::update_and_render(SDL_Renderer* renderer, int limit_radius)
{
  this->time_passed += 1.0 / 60;

  
  if(this->time_passed >= this->lifespan)
  {
    
    this->is_active = false;
    time_passed = 0.0f;

  }
  
  for (int i = 0; i < num_of_particles; i++)
    {
      particles[i].current_x += particles[i].dx / 60.0;
      particles[i].current_y += particles[i].dy / 60.0;

      this->particle_rect.x = int(particles[i].current_x);
      this->particle_rect.y = int(particles[i].current_y);
      
      if (
	  (particles[i].current_x >= limit_radius + this->origin_x) ||
	  (particles[i].current_x <= this->origin_x - limit_radius) ||
	  (particles[i].current_y >= limit_radius + this->origin_y) ||
	  (particles[i].current_y <= this->origin_y - limit_radius)
	 )
	{
	  particles[i].respawn(this->origin_x, this->origin_y);
	}

      SDL_RenderCopy(renderer, this->texture, NULL, &this->particle_rect);
    }
}
