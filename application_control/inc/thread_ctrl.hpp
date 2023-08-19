/** @file thread_ctrl.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for threading control..
 * 
 * @par This file contains the various types used for controlling threads.
 * 
 */

#ifndef TULIP_THREAD_CTRL_H_
  #define TULIP_THREAD_CTRL_H_

  #include <SDL.h>
  #include <SDL_thread.h>
  #include <vector>
  #include <renderer.hpp>
  #include <timers.hpp>

  /** @brief This struct is used to organize the various control mechanisms for threading. */
  typedef struct thread_vars
  {
    Screen*      engine_window;
    SDL_cond*    update_screen;
    SDL_mutex*   update_screen_mutex;
    SDL_sem*     sem;
    bool         kill;
    SDL_TimerID  renderTimerID;
  } thread_vars_t;

  /** @brief This enumerate tracks all of the available threads. */
  enum thread_types
  {
    E_RENDER,
    E_NUM_THREADS
  };

  typedef thread_types thread_types_t;

  // Function declarations
  SDL_ThreadFunction thread_GetThreadPtr(thread_types_t t);

#endif /* TULIP_THREAD_CTRL_H_ */
