/** @file events.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for tulip event handling.
 * 
 * @par This file contains the relevant definitions and function declarations for event handling for the tulip game engine.
 * 
 */

#pragma once
  // Dependencies
  #include <stdbool.h>
  #include <SDL.h>

  // Function declarations
  SDL_Event* CreateEvent(void);
  bool PollEvent(SDL_Event* e);
