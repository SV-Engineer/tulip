/** @file ui_mouse_input.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for tulip mouse input handling.
 * 
 * @par This file contains the header for the mouse handling events.
 * 
 */

#ifndef TULIP_MOUSE_INPUT_H_
  #define TULIP_MOUSE_INPUT_H_

  // Dependencies
  #include <stdbool.h>
  #include <SDL.h>

  typedef struct mouse_input
  {
    int x;
    int y;
  } mouse_input_t;

  // Function Declarations
mouse_input_t mouse_GetLocation(void);

#endif /* TULIP_MOUSE_INPUT_H_ */
