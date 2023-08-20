/** @file events.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for tulip event handling.
 * 
 * @par This file contains the relevant definitions and function declarations for event handling for the tulip game engine.
 * 
 */

#ifndef TULIP_EVENTS_H_
  #define TULIP_EVENTS_H_
  // Dependencies
  #include <stdbool.h>
  #include <SDL.h>
  #include <mouse_input.hpp>
  #include <thread_ctrl.hpp>

  // Function declarations
  SDL_Event* evt_CreateEvent(void);
  void evt_PollEvent(SDL_Event* e, thread_vars_t* ctrl);

#endif /* TULIP_EVENTS_H_ */
