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
  // Dependencies.
  #include <SDL.h>

  #define DEBUG
  #ifdef DEBUG
    #include <string>
    #include <iostream>
    #define INFO(X)         std::cout << "*INFO: " #X << std::endl
    #define ERR(X,Y)        std::cout << "*ERR: "  #X << Y << std::endl
  #else
    #define INFO(X)
    #define ERR(X,Y)
  #endif

  // Types and objects
  
  typedef struct sdl_renderer {
    SDL_Window*  window;
    SDL_Surface* surface;
  } sdl_renderer_t;

  class SDL_WindowRenderer
  {
    private:
      sdl_renderer_t renderer;

    public:
      // Class constructor
      SDL_WindowRenderer(sdl_renderer_t r)
      {
        renderer = r;
      }

      // Class destructor
      ~SDL_WindowRenderer(void)
      {
        //Destroy window
        SDL_DestroyWindow(renderer.window);
        //Quit SDL subsystems
        SDL_Quit();
      }

      // Object retrieval
      SDL_Window* Get_sdl_window(void)
      {
        return renderer.window;
      }

  }; /* SDL_WindowRenderer */

  // Function declarations.
  SDL_WindowRenderer* create_renderer(void);
  void kill_renderer(SDL_WindowRenderer* renderer);

#endif /* TULIP_RENDERER_H_ */
