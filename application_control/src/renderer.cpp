/** @file renderer.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip rendering.
 * 
 * @par This file contains the source for the top level abstraction 
 * of rendering images to the screen.
 * 
 */

#include <renderer.hpp>

/** @fn Screen* create_renderer(void)
 * @brief This instantiates and returns a pointer to a heap
 * allocated class containging an SDL window and surface.
 * 
 * @return Screen*
 * A pointer to a heap allocated class for window handling.
 * 
 * @return NULL
 * Returns NULL if the window fails to initialize.
 */
Screen* create_renderer(void)
{
  Screen* screen = new Screen();

  if (screen->Get_sdl_window() == NULL)
  {
    ERR("Window could not be created! SDL_Error: ", SDL_GetError());
    kill_renderer(screen);
    return NULL;
  }

  else
  {
    INFO("SDL Window successfully created.");
    return screen;
  }
} /* create_renderer */

/** @fn void kill_renderer(Screen* renderer)
 * @brief This destroys the window handling class.
 * 
 * @param renderer
 * The object created to handle the SDL window.
 * 
 * @return void
 */
void kill_renderer(Screen* screen)
{
  delete screen;
} /* kill_renderer */
