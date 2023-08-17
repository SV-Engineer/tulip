/** @file timers.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for tulip timers.
 * 
 * @par This file contains the dependencies for the timers source file.
 * 
 */

#ifndef TULIP_TIMERS_H_
  #define TULIP_TIMERS_H_

  // Dependencies.
  #include <SDL.h>
  #include <thread_ctrl.hpp>
  #include <debug.hpp>

  // Function declarations
  SDL_TimerID timer_InitRenderTimer(void* ctrl);
  void timer_KillTimer(SDL_TimerID id);

#endif /* TULIP_TIMERS_H_ */
