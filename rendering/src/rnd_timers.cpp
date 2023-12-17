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
 * A vector of timers and their associated names
 */
Timers_t rnd_init_timers(void)
{
  Timers_t timers
  {
    {"refresh", new Tulip_timer(17 /* 59 Hz for now */)}
  };


  if (timers["refresh"] = nullptr)
  {
    ERR("Screen refresh timer creation unsuccessful, SDL Error: ", SDL_GetError());
    return timers;
  }

  else
  {
    return timers;
  }

}
