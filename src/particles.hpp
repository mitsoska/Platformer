const int total_particles = 20;

class Particles
{
public:

  SDL_Texture* texture;
  SDL_Rect particle_rectangle;
 
public:

  Particle(int x, int y);

  void render();


private:

  int offset_x, offset_y;

  int current_frame;


}
