/** @file draw_square/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for following the mouse.
 * 
 * @par This file contains the unit test used to sanity check the ability to track the mouse.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile all UT=mouse_tracking
 */

#include <debug.hpp>
#include <TULIP_ApplicationControl.hpp>

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

// Main Unit test function.
int unit_test(void)
{
  volatile thread_vars_t  ctrl                  = {};

  SDL_Thread*             thread_process_render = nullptr;
  SDL_Thread*             thread_process_input  = nullptr;

  // Assign pointers and default values to structure.
  INFO("Assigning Pointers to structure");
  ctrl.kill                          = false;
  ctrl.sem                           = SDL_CreateSemaphore(0x1U);
  ctrl.engine_window                 = rend_CreateRenderer();
  ctrl.e                             = evt_CreateEvent();

  if ((ctrl.sem == NULL) || (ctrl.engine_window == NULL))
  {
    ERR("Semaphore or Engine Window not initialized.", SDL_GetError());
    return FAILURE;
  }

  else
  {
    timer_InitTimers((void*) &ctrl);
    // Start the rendering thread and detach it.
    INFO("Starting thread(s)");
    thread_process_render = SDL_CreateThread(thread_GetThreadPtr(E_RENDER), "rendering",  (void*) &ctrl);
    thread_process_input  = SDL_CreateThread(thread_GetThreadPtr(E_KB_INPUT), "kb_input", (void*) &ctrl);
    SDL_DetachThread(thread_process_render);
    SDL_DetachThread(thread_process_input);

    INFO("Entry to event polling thread. Polling exit event.");
    do
    {
      SDL_SemWait(ctrl.sem);
      evt_PollEvent((thread_vars_t*) &ctrl);
      SDL_SemPost(ctrl.sem);
    } while (!(ctrl.kill));
    INFO("Quit Event Detected");

    SDL_DestroySemaphore(ctrl.sem);
    timer_KillTimers(((thread_vars_t *) &ctrl)->timerIDs);

    INFO("Exiting main loop.");

    return SUCCESS;
  }
} /* unit_test */
