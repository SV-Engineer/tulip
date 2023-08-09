/** @file renderer.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for tulip rendering.
 * 
 * @par This file contains the header for the top level abstraction 
 * of rendering images to the screen.
 * 
 */

#ifndef TULIP_RENDERER_H_
  #define TULIP_RENDERER_H_
  #define DEBUG
  // Dependencies.
  #include <SDL.h>
  #include <debug.hpp>

  // Macro Definitions
  #define WINDOWED_SCREEN_WIDTH    640
  #define WINDOWED_SCREEN_HEIGHT   480

  // Types, Objects and Classes
  class Screen
  {
    private:
      SDL_Window*  window;
      SDL_Surface* surface;

    public:
      // Class constructor
      Screen(void)
      {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
          ERR("SDL could not initialize! SDL_Error: ", SDL_GetError());
        }

        else
        {
          // Create a window and get its surface.
          window = SDL_CreateWindow("tulip-engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWED_SCREEN_WIDTH, WINDOWED_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
          surface = SDL_GetWindowSurface(window);
          //Fill the surface black
          SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
          //Update the surface
          SDL_UpdateWindowSurface(window);
        }
      }

      // Class destructor
      ~Screen(void)
      {
        //Destroy window
        SDL_DestroyWindow(window);
        //Quit SDL subsystems
        SDL_Quit();
      }

      // Object retrieval
      SDL_Window* Get_sdl_window(void)
      {
        return window;
      }

  }; /* Screen */

  // Function declarations.
  Screen* create_renderer(void);
  void kill_renderer(Screen* renderer);

#endif /* TULIP_RENDERER_H_ */
