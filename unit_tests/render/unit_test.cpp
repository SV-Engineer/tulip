/** @file render/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for rendering with events.
 * 
 * @par This file contains the unit test used to sanity check the event control logic 
 * combined with the renderer in the application control module.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile all UT=render
 */

#include <events.hpp>
#include <renderer.hpp>

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

int unit_test(void)
{
  // Perform pointer initializations.
  Screen* engine_window = rend_CreateRenderer();
  SDL_Event* e = evt_CreateEvent();

  if ((engine_window == NULL) || (e == NULL))
  {
    return FAILURE;
  }

  else
  {
    // Wait on quit event and then exit program.
    while (!evt_PollEvent(e));
    rend_KillRenderer(engine_window);
    return SUCCESS;
  }
} /* unit_test */
