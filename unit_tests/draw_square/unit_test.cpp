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

#define DEBUG
#include <debug.hpp>
#include <SDL_thread.h>
#include <events.hpp>
#include <renderer.hpp>

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

// Forward declare the threads.
int thread_RenderScreen(void*);
int thread_EvtHandler(void*);

typedef struct thread_vars
{
  SDL_sem*  sem;
  bool      kill;
} thread_vars_t;

// Main Unit test function.
int unit_test(void)
{
  // Using the semaphore as a mutex (for now).
  volatile SDL_sem*       thread_semaphore = SDL_CreateSemaphore(0x1U);
  volatile thread_vars_t  thread_deciders  = {};
  volatile bool           exit_req         = false;

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
    thread_deciders.sem            = (SDL_sem*) thread_semaphore;
    INFO("Update Kill");
    thread_deciders.kill           = false;

    // Start the event handler thread.
    INFO("Starting threads");
    SDL_Thread* thread_process_event  = SDL_CreateThread(thread_EvtHandler, "eventThread", (void*) &thread_deciders);
    SDL_Thread* thread_process_render = SDL_CreateThread(thread_RenderScreen, "rendering", (void*) &thread_deciders);

    SDL_DetachThread(thread_process_render);
    
    INFO("Waiting on kill in main thread.");
    // do
    // {
    //   SDL_SemWait(thread_deciders.sem);
    //   exit_req = thread_deciders.kill;
    //   SDL_SemPost(thread_deciders.sem);
    // } while (!(exit_req));
    SDL_WaitThread(thread_process_event, NULL);

    INFO("Kill detected.");

    SDL_DestroySemaphore(thread_deciders.sem);
    return SUCCESS;
  }
} /* unit_test */


int thread_EvtHandler(void* thread_variables)
{
  thread_vars_t* ctrl = (thread_vars_t*) thread_variables;
  SDL_Event*     e    = evt_CreateEvent();

  INFO("Entry to event polling thread.");
  do
  {
    SDL_SemWait(ctrl->sem);
    ctrl->kill = evt_PollEvent(e);
    SDL_SemPost(ctrl->sem);
  } while (!(ctrl->kill));

  INFO("Quit Event Detected");

  return SUCCESS;
} /* thread_EvtHandler */

int thread_RenderScreen(void* thread_variables)
{
  // Perform pointer initialization.
  Screen*        engine_window = rend_CreateRenderer();
  thread_vars_t* ctrl          = (thread_vars_t*) thread_variables;
  // Test variables
  int h = 1;
  int v = 1;
  uint8_t red_sat = (uint8_t) 0xFF;
  bool exit = false;


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
      // Initialize the back buffer.
      SDL_RenderClear(engine_window->Get_sdl_renderer());

      // Set the renderer's drawing color.
      (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), red_sat--, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0xFF);

      // Draw a line of points across the screen.
      SDL_RenderDrawPoint(engine_window->Get_sdl_renderer(), h, v);

      // Update to present.
      SDL_RenderPresent(engine_window->Get_sdl_renderer());

      SDL_Delay(16U);

      SDL_SemWait(ctrl->sem);
      exit = ctrl->kill;
      SDL_SemPost(ctrl->sem);
    }

    INFO("Kill Renderer");
    rend_KillRenderer(engine_window);
  }

  return SUCCESS;
} /* thread_RenderScreen */
