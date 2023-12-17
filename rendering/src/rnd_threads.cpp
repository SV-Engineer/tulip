/** @file rnd_threads.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the rendering threads.
 * 
 * @par This file is the source for the rendering threads.
 * 
 */

#include "rnd_threads.hpp"

// SDL_ThreadFunction
// SDL_Thread


/** @fn static int rnd_thrd_update_screen (void* ctrl)
 * @brief This function is to be used as a thread.
 * 
 * 
 * @return 0
 * Success
 * 
 * @return -1
 * Failure
 * 
 */
static int rnd_thrd_update_screen (void* ctrl)
{
  Rnd_Screen* screen = (Rnd_Screen*) ctrl;
}
