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
  #include <vector>
  #include <debug.hpp>

  // Function declarations
  void timer_InitTimers(void* ctrl);
  void timer_KillTimers(std::vector<SDL_TimerID> ids);

#endif /* TULIP_TIMERS_H_ */
