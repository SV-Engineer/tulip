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
  volatile thread_vars_t  thread_deciders       = {};
  SDL_Event*              e                     = evt_CreateEvent();
  SDL_Thread*             thread_process_render = nullptr;

  // Assign pointers and default values to structure.
  INFO("Assigning Pointers to structure");
  thread_deciders.kill                          = false;
  thread_deciders.sem                           = SDL_CreateSemaphore(0x1U);
  thread_deciders.engine_window                 = rend_CreateRenderer();
  thread_deciders.update_screen                 = SDL_CreateCond();
  thread_deciders.update_screen_mutex           = SDL_CreateMutex();
  thread_deciders.renderTimerID                 = timer_InitRenderTimer((void*) &thread_deciders);

  if
  (
      (thread_deciders.sem == NULL)
   || (thread_deciders.engine_window == NULL)
   || (thread_deciders.update_screen == NULL)
   || (thread_deciders.update_screen_mutex == NULL)
  )
  {
    ERR("Semaphore or Engine Window or Condition Variable or Mutex not initialized.", SDL_GetError());
    return FAILURE;
  }

  else
  {
    // Start the rendering thread and detach it.
    INFO("Starting thread(s)");
    thread_process_render = SDL_CreateThread(thread_RenderScreen, "rendering", (void*) &thread_deciders);
    SDL_DetachThread(thread_process_render);

    INFO("Entry to event polling thread. Polling exit event.");
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

    INFO("Quit Event Detected");

    SDL_DestroySemaphore(thread_deciders.sem);

    INFO("Exiting main loop.");
    return SUCCESS;
  }
} /* unit_test */

int thread_RenderScreen(void* thread_variables)
{
  // Perform pointer initialization.
  thread_vars_t* ctrl          = (thread_vars_t*) thread_variables;
  Screen*        engine_window = ctrl->engine_window;
  // Test variables
  volatile bool exit = false;
  int h = 1;
  int v = 1;
  SDL_Rect tmp_rect =
  {
    .x = (DEFAULT_WINDOWED_SCREEN_WIDTH >> 1),
    .y = (DEFAULT_WINDOWED_SCREEN_HEIGHT >> 2),
    .w = 64,
    .h = 64
  };

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


      // Set rectangle color
      (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), (uint8_t) 0x00, (uint8_t) 0xFF, (uint8_t) 0x00, (uint8_t) 0xFF);
      (void) SDL_RenderFillRect(engine_window->Get_sdl_renderer(), (const SDL_Rect*) &tmp_rect);

      // Set the renderer's drawing color.
      (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), 0x00, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0xFF);

      // Draw a "square"
      SDL_RenderDrawRect(engine_window->Get_sdl_renderer(), &tmp_rect);

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

    rend_KillRenderer(engine_window);
    timer_KillTimer(ctrl->renderTimerID);
  }

  return SUCCESS;
} /* thread_RenderScreen */
