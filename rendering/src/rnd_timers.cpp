/** @file rnd_timers.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the rendering timers.
 * 
 * @par This file is the source for the rendering timers.
 * 
 */

#include "rnd_timers.hpp"

/** @fn Timers_vect_t rnd_init_timers(void)
 * @brief This creates a vector of timers and returns them so they may 
 * be associated with their respective threads.
 * 
 * @return Timers_vect_t
 * A pointer to a vector of timers and their associated names
 */
Timers_vect_t* rnd_init_timers(void)
{
  Timers_vect_t*   timers         = new Timers_vect_t;
  Timer_instance_t timer_instance = {nullptr, ""};

  // Allocate the class handles on the heap so they remain.
  // Screen Refresh
  timer_instance.Handle           = new Tulip_timer(17 /* 59 Hz for now */);
  timer_instance.Name             = (const std::string) "refresh";

  if (timer_instance.Handle = nullptr)
  {
    ERR("Screen refresh timer creation unsuccessful, SDL Error: ", SDL_GetError());
  }

  else
  {
    timers->push_back(timer_instance);

    // Set back to null
    timer_instance = {nullptr, ""};
  }

  return timers;
}
