/** @file renderer.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip rendering.
 * 
 * @par This file contains the source for the top level abstraction 
 * of rendering images to the screen.
 * 
 */

#include <renderer.hpp>

#define WINDOWED_SCREEN_WIDTH    640
#define WINDOWED_SCREEN_HEIGHT   480

static sdl_renderer_t hlp_CreateWindow(void);

SDL_WindowRenderer* create_renderer(void)
{
  return (new SDL_WindowRenderer(hlp_CreateWindow()));
}

void kill_renderer(SDL_WindowRenderer* renderer)
{
  delete renderer;
}

static sdl_renderer_t hlp_CreateWindow(void)
{
  // Declare objects
  sdl_renderer_t w = {.window = NULL, .surface = NULL};

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    ERR("SDL could not initialize! SDL_Error: ", SDL_GetError());
    return w;
  }

  else
  {
    //Create window
    w.window = SDL_CreateWindow("tulip-engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWED_SCREEN_WIDTH, WINDOWED_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Ensure the window has been created.
    if(w.window == NULL)
    {
      ERR("Window could not be created! SDL_Error: ", SDL_GetError());
      return w;
    }

    else
    {
      INFO("SDL Window successfully created.");

      //Get window surface
      w.surface = SDL_GetWindowSurface(w.window);

      //Fill the surface black
      SDL_FillRect(w.surface, NULL, SDL_MapRGB(w.surface->format, 0x00, 0x00, 0x00));
      
      //Update the surface
      SDL_UpdateWindowSurface(w.window);

      // Return the window pointer.
      return w;
    }
  }
}