/** @file draw_square/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for drawing a square on the renderer.
 * 
 * @par This file contains the unit test used to sanity check the renderer's ability to create polygons.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile all UT=draw_square
 */

#include <debug.hpp>
#include <TULIP_ApplicationControl.hpp>

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

// Forward declare the threads.
int thread_RenderScreen(void*);
//int thread_EvtHandler(void*);

// Main Unit test function.
int unit_test(void)
{
  // Using the semaphore as a mutex (for now).
  Screen*                 engine_window    = rend_CreateRenderer();
  SDL_Event*              e                = evt_CreateEvent();
  volatile SDL_sem*       thread_semaphore = SDL_CreateSemaphore(0x1U);
  volatile thread_vars_t  thread_deciders  = {};

  if (thread_semaphore == NULL)
  {
    ERR("Semaphore not initalized.", SDL_GetError());
    return FAILURE;
  }

  else
  {
    // Assign pointers and default values to structure.
    INFO("Assigning Pointers to structure");
    INFO("Update Sem");
    thread_deciders.sem                 = (SDL_sem*) thread_semaphore;
    INFO("Update Kill");
    thread_deciders.kill                = false;
    thread_deciders.engine_window       = engine_window;
    thread_deciders.update_screen       = SDL_CreateCond();
    thread_deciders.update_screen_mutex = SDL_CreateMutex();
    thread_deciders.renderTimerID       = timer_InitRenderTimer((void*) &thread_deciders);

    // Start the event handler thread.
    INFO("Starting threads");
    // SDL_Thread* thread_process_event  = SDL_CreateThread(thread_EvtHandler, "eventThread", (void*) &thread_deciders);
    SDL_Thread* thread_process_render = SDL_CreateThread(thread_RenderScreen, "rendering", (void*) &thread_deciders);

    SDL_DetachThread(thread_process_render);

    INFO("Waiting on kill in main thread.");

    INFO("Entry to event polling thread.");
    do
    {
      if(SDL_SemTryWait(thread_deciders.sem) == SUCCESS)
      {
        thread_deciders.kill = evt_PollEvent(e);
        SDL_SemPost(thread_deciders.sem);
      }

      else
      {
        continue;
      }
    } while (!(thread_deciders.kill));

    //SDL_WaitThread(thread_process_render, NULL);
    INFO("Quit Event Detected");


    //(void) thread_EvtHandler((void*) &thread_deciders);


    INFO("Kill detected.");

    SDL_DestroySemaphore(thread_deciders.sem);

    return SUCCESS;
  }
} /* unit_test */

int thread_RenderScreen(void* thread_variables)
{
  // Perform pointer initialization.
  thread_vars_t* ctrl          = (thread_vars_t*) thread_variables;
  Screen*        engine_window = ctrl->engine_window;
  // Test variables
  int h = 1;
  int v = 1;
  uint8_t red_sat = (uint8_t) 0xFF;
  volatile bool exit = false;


  if ((engine_window == NULL))
  {
    ERR("Screen returned null pointer", SDL_GetError());
  }

  else
  {
    INFO("Enter Rendering loop.");
    // Enter rendering thread loop.
    while (!exit)
    {

      //SDL_mutexP(ctrl->update_screen_mutex);
      (void) SDL_CondWait(ctrl->update_screen, ctrl->update_screen_mutex);

      // Initialize the back buffer.
      SDL_RenderClear(engine_window->Get_sdl_renderer());

      // Set the renderer's drawing color.
      (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), red_sat--, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0xFF);

      // Draw a line of points across the screen.
      SDL_RenderDrawPoint(engine_window->Get_sdl_renderer(), (h++ & (DEFAULT_WINDOWED_SCREEN_WIDTH - 1)), (v++ & (DEFAULT_WINDOWED_SCREEN_HEIGHT - 1)));

      // Update to present.
      SDL_RenderPresent(engine_window->Get_sdl_renderer());

      if(SDL_SemTryWait(ctrl->sem) == SUCCESS)
      {
        exit = ctrl->kill;
        SDL_SemPost(ctrl->sem);
      }

      else
      {
        continue;
      }
    }

    INFO("Kill Renderer");
    rend_KillRenderer(engine_window);
  }

  return SUCCESS;
} /* thread_RenderScreen */
