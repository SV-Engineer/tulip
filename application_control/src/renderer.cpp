/** @file renderer.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip rendering.
 * 
 * @par This file contains the source for the top level abstraction 
 * of rendering images to the screen.
 * 
 */

#include <renderer.hpp>

/** @fn Screen* rend_CreateRenderer(void)
 * @brief This instantiates and returns a pointer to a heap
 * allocated class containging an SDL window and surface.
 * 
 * @return Screen*
 * A pointer to a heap allocated class for window handling.
 * 
 * @return NULL
 * Returns NULL if the window fails to initialize.
 */
Screen* rend_CreateRenderer(void)
{
  Screen* screen = new Screen();

  if ((screen->Get_sdl_window() == NULL) || (screen->Get_sdl_renderer() == NULL))
  {
    ERR("Window or renderer could not be created! SDL_Error: ", SDL_GetError());
    rend_KillRenderer(screen);
    return NULL;
  }

  else
  {
    INFO("SDL Window successfully created.");
    return screen;
  }
} /* rend_CreateRenderer */

/** @fn void rend_KillRenderer(Screen* renderer)
 * @brief This destroys the window handling class.
 * 
 * @param renderer
 * The object created to handle the SDL window.
 * 
 * @return void
 */
void rend_KillRenderer(Screen* screen)
{
  INFO("Quit Event Received. Destroying Renderer.");
  delete screen;
} /* rend_KillRenderer */
