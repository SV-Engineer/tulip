/** @file compilation/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for compilation.
 * 
 * @par This file contains the unit test used to ensure the SDL2 libraries can be compiled.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile all UT=compilation
 */

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
#define SCREEN_WIDTH     640
#define SCREEN_HEIGHT    480

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

void init_sdl(void);

/** @fn int unit_test (void)
 * @brief The unit test function definition.
 * 
 * @return Zero implies success and negative numbers imply error. Positive numbers imply warnings.
 */
int unit_test(void)
{
  init_sdl();
  return 0;
} /* unit_test */

void init_sdl(void)
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
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
            
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

} /* init_sdl */
