/** @file timers.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip timers.
 * 
 * @par This file contains the source for the creating, using, and destroying timers.
 * 
 */

#include <timers.hpp>

// Forward declare helper functions
uint32_t hlp_SignalThread(uint32_t interval, void* param);

/** @fn SDL_TimerID timer_InitRenderTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the rendering thread to run.
 * 
 * @return SDL_TimerID
 * A pointer to a timer.
 * 
 * @return 0
 * Returns 0 if the timer fails to initialize.
 */
SDL_TimerID timer_InitRenderTimer(void* ctrl)
{
  thread_vars_t* ctrl_local = (thread_vars_t *) ctrl;
  SDL_mutexP(ctrl_local->update_screen_mutex);
  SDL_TimerID render_timer = SDL_AddTimer(16 /* 16.6 ms is 60 Hz*/, hlp_SignalThread, ctrl);
  return render_timer;
} /* timer_InitRenderTimer */

/** @fn void timer_KillTimer(SDL_TimerID id)
 * @brief This function instantiates a timer used to signal the rendering thread to run.
 * 
 * @param SDL_TimerID
 * ID of the Timer to destroy.
 */
void timer_KillTimer(SDL_TimerID id)
{
  SDL_RemoveTimer(id);
}


/** @fn uint32_t hlp_SignalThread(uint32_t interval, void* param)
 * @brief This function is the call back function for the timers.
 * 
 * @param void*
 * A void pointer to a @ref thread_ctrl_t type
 */
uint32_t hlp_SignalThread(uint32_t interval, void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;
  int status = SDL_CondSignal(ctrl->update_screen);
  SDL_mutexV(ctrl->update_screen_mutex);
  return interval;
} /* hlp_SignalThread */