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
  #define DEFAULT_WINDOWED_SCREEN_WIDTH    512
  #define DEFAULT_WINDOWED_SCREEN_HEIGHT   256

  // Types, Objects and Classes
  class Screen
  {
    private:
      SDL_Window*  window;
      SDL_Surface* surface;
      SDL_Renderer* renderer;

      /** @memberof Screen
       * @fn SDL_Renderer* hlp_GetRendererDrivers(SDL_Window* w)
       * @brief This instantiates and returns a pointer to a heap
       * allocated class containging an SDL window and surface.
       * 
       * @return SDL_Renderer*
       * A pointer to an SDL_Renderer
       * 
       * @return nullptr
       * Returns nullptr if renderer fails to initialize.
       */
      SDL_Renderer* hlp_GetRendererDrivers(SDL_Window* w)
      {
        SDL_Renderer* r = nullptr;
        for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
        {
          // TIL that initializing a struct with empty curly braces is
          // a succinct way of guaranteeing all members are initialized
          // to default values. I.e an 'int' type would be initialized to
          // a value of `0` while a 'float' or 'double' will be initialized
          // to a value of `0.0`.
          SDL_RendererInfo r_info = {};
          SDL_GetRenderDriverInfo(i, &r_info);

          // Check for direct3d11
          if (r_info.name == std::string("direct3d11"))
          {
            INFO("direct3d11 found");
            r = SDL_CreateRenderer(w, i , 0);
            break;
          }

          // It is preffered to not leave undefined paths when possible.
          else
          {
            continue;
          }
        }

        if (r != NULL)
        {
          SDL_SetRenderDrawColor(r, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0xFF);
          // Return the pointer. The initialization function will do error checking.
          return r;
        }

        else
        {
          return r;
        }
      }

    public:
      // Class constructor
      Screen(void)
      {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
          ERR("SDL could not initialize! SDL_Error: ", SDL_GetError());
          window   = nullptr;
          surface  = nullptr;
          renderer = nullptr;
        }

        else
        {
          // Tell SDL that direct3d11 will be used if available.
          // Cast to void as we will not use the return boolean.
          (void) SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");

          // Create a window and get its surface.
          window = SDL_CreateWindow("tulip-engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WINDOWED_SCREEN_WIDTH, DEFAULT_WINDOWED_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

          // Create a renderer
          renderer = hlp_GetRendererDrivers(window);

          surface = SDL_GetWindowSurface(window);
          //Fill the surface black
          SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
          //Update the surface
          SDL_UpdateWindowSurface(window);
        }
      } /* constructor */

      // Class destructor
      ~Screen(void)
      {
        // Destroy Renderer
        if (renderer != NULL)
        {
          SDL_DestroyRenderer(renderer);
        }

        //Destroy window
        if (window != NULL)
        {
          SDL_DestroyWindow(window);
        }

        //Quit SDL subsystems
        SDL_Quit();
      } /* destructor */

      // ===============================================================
      // Object retrieval
      // ===============================================================

      /** @memberof Screen
       * @fn SDL_Window* Get_sdl_window(void)
       * @brief This returns a pointer to the instantiated window.
       * 
       * @return SDL_Window*
       * A pointer to an SDL_Window
       * 
       * @return nullptr
       * Returns nullptr if window failed to initialize.
       */
      SDL_Window* Get_sdl_window(void)
      {
        return window;
      } /* Get_sdl_window */

      /** @memberof Screen
       * @fn SDL_Renderer* Get_sdl_renderer(void)
       * @brief This returns a pointer to the instantiated renderer.
       * 
       * @return SDL_Renderer*
       * A pointer to an SDL_Renderer
       * 
       * @return nullptr
       * Returns nullptr if renderer failed to initialize.
       */
      SDL_Renderer* Get_sdl_renderer(void)
      {
        return renderer;
      } /* Get_sdl_renderer */

  }; /* Screen */

  // Function declarations.
  Screen* rend_CreateRenderer(void);
  void rend_KillRenderer(Screen* renderer);

#endif /* TULIP_RENDERER_H_ */
