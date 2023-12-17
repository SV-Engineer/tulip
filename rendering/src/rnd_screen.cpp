/** @file rnd_screen.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the screen rendering.
 * 
 * @par This file is the source for the screen rendering.
 * 
 */

#include "rnd_screen.hpp"

/** @fn Rnd_Screen rnd_create_renderer(void)
 * @brief This instantiates and returns a pointer to a heap
 * allocated class containging an SDL window and surface.
 * 
 * @return Rnd_Screen
 * An pointer to an instantiation of the Render Screen class.
 * 
 * @return NULL
 * Returns NULL if the window fails to initialize.
 */
Rnd_Screen* rnd_init_renderer(void)
{
  Rnd_Screen* screen = new Rnd_Screen;

  if ((screen->Get_window() == NULL) || (screen->Get_renderer() == NULL))
  {
    ERR("Window or renderer could not be created! SDL_Error: ", SDL_GetError());
    delete screen;
    return NULL;
  }

  else
  {
    INFO("SDL Window successfully created.");
    return screen;
  }
} /* rnd_CreateRenderer */
