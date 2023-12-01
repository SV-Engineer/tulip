/** @file ui_timers.hpp
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

  enum
  {
    E_IDLE,
    E_INPUT,
    E_RENDER
  };

  // Function declarations
  void timer_InitTimers(void*, uint32_t = 0xFFFFFFFFU);
  void timer_KillTimers(void*);

#endif /* TULIP_TIMERS_H_ */
