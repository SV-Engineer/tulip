/** @file thread_ctrl.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip timers.
 * 
 * @par This file contains the source for the threads.
 * 
 */

#include <thread_ctrl.hpp>
#include <events.hpp>

// Forward declare functions
static int thread_RenderScreen(void* thread_variables);
static int thread_UserInput(void* thread_variables);

/** @fn SDL_ThreadFunction thread_GetThreadPtr(thread_types_t t)
 * @brief This function is to be used to get the appropriate function pointer for the desired thread.
 * 
 * @param @ref threads_t
 * 
 * @return SDL_ThreadFunction
 * 
 */
SDL_ThreadFunction thread_GetThreadPtr(thread_types_t t)
{
  SDL_ThreadFunction tmp_thread = nullptr;
  switch (t)
  {
    case E_RENDER:
      tmp_thread = thread_RenderScreen;
      break;

    case E_KB_INPUT:
      tmp_thread = thread_UserInput;
      break;

    default:
      tmp_thread = nullptr;
      break;
  }

  return tmp_thread;
} /* thread_GetThreadPtr */

/** @fn static int thread_UserInput(void* thread_variables)
 * @brief This function is to be used as a thread.
 * 
 * @par Use thread_GetThreadPtr to retrieve this thread.
 * See Also:
 *    * @ref E_KB_INPUT
 *    * @ref threads_t
 * 
 * @return @ref SUCCESS
 * 
 */
static int thread_UserInput(void* thread_variables)
{
  thread_vars_t* ctrl = (thread_vars_t*) thread_variables;
  volatile bool  exit = false;

  while (!exit)
  {
    (void) SDL_CondWait(ctrl->signal_update[THREAD_INPUT], ctrl->mutexes[THREAD_INPUT]);

    if(ctrl->key_pressed == SDLK_w)
    {
      INFO("W press detected");
    }

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

  return SUCCESS;
} /* thread_UserInput */


/** @fn static int thread_RenderScreen(void* thread_variables)
 * @brief This function is to be used as a thread.
 * 
 * @par Use thread_GetThreadPtr to retrieve this thread.
 * See Also:
 *    * @ref E_RENDER 
 *    * @ref threads_t
 * 
 * @return @ref SUCCESS
 * 
 */
static int thread_RenderScreen(void* thread_variables)
{
  // Perform pointer initialization.
  thread_vars_t* ctrl          = (thread_vars_t*) thread_variables;
  Screen*        engine_window = ctrl->engine_window;
  volatile bool  exit = false;


  INFO("Enter Rendering loop.");
  // Enter rendering thread loop.
  while (!exit)
  {

    //SDL_mutexP(ctrl->update_screen_mutex);
    (void) SDL_CondWait(ctrl->signal_update[THREAD_RENDER], ctrl->mutexes[THREAD_RENDER]);

    // Initialize the back buffer.
    SDL_RenderClear(engine_window->Get_sdl_renderer());

    // Set rectangle color
    // (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), (uint8_t) 0x00, (uint8_t) 0xFF, (uint8_t) 0x00, (uint8_t) 0xFF);
    // (void) SDL_RenderFillRect(engine_window->Get_sdl_renderer(), (const SDL_Rect*) &tmp_rect);

    // Set the renderer's drawing color.
    (void) SDL_SetRenderDrawColor(engine_window->Get_sdl_renderer(), 0x00, (uint8_t) 0x00, (uint8_t) 0x00, (uint8_t) 0xFF);

    // Draw a "square"
    // SDL_RenderDrawRect(engine_window->Get_sdl_renderer(), &tmp_rect);

    // Update to present.
    SDL_RenderPresent(engine_window->Get_sdl_renderer());
    // Update Surface
    SDL_UpdateWindowSurface(engine_window->Get_sdl_window());

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
  return SUCCESS;
} /* thread_RenderScreen */
