/** @file common_timers/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for checking if the common timers work.
 * 
 * @par This file contains the unit test used to ensure the common timers work as intended.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile test UT=common_timers
 */

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <common_timers.hpp>

//Screen dimension constants
#define SCREEN_WIDTH     640
#define SCREEN_HEIGHT    480

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

int test_timer(void);

/** @fn int unit_test (void)
 * @brief The unit test function definition.
 * 
 * @return Zero implies success and negative numbers imply error. Positive numbers imply warnings.
 */
int unit_test(void)
{
  return test_timer();
} /* unit_test */

int test_timer(void)
{
  //The window we'll be rendering to
  SDL_Window* window = NULL;
  
  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  else
  {
    //Create window
    window = SDL_CreateWindow( "Common Timers - See console, not window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
      //Get window surface
      screenSurface = SDL_GetWindowSurface( window );

      //Fill the surface white
      SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

      //Update the surface
      SDL_UpdateWindowSurface( window );

      Tulip_timer * test_timer1 = new Tulip_timer(2500);
      Tulip_timer * test_timer2 = new Tulip_timer(1000);

      //Hack to get window to stay up
      SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    }
  }

  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();

} /* init_sdl */
