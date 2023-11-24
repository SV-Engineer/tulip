/** @file mouse_input.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip mouse input handling.
 * 
 * @par This file contains the source for the mouse handling events.
 * 
 */

#include <mouse_input.hpp>

mouse_input_t mouse_GetLocation(void)
{
  mouse_input_t mouse_loc = {};

  SDL_GetMouseState(&(mouse_loc.x), &(mouse_loc.y));

  return mouse_loc;
} /* mouse_GetLocation */
