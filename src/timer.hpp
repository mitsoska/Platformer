#ifndef _TIMER_H
#define _TIMER_H


#include <SDL2/SDL.h>

class Timer
{
public:
  float starting_time = 0.0f;
  float duration;

public:
  Timer(float duration);

  bool is_running();

  void restart(float duration);

  float get_time_running();
  
};


#endif
