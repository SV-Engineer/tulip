/** @file timers.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip timers.
 * 
 * @par This file contains the source for the creating, using, and destroying timers.
 * 
 */

#include <timers.hpp>

// Forward declare helper functions
uint32_t hlp_SignalRenderThread(uint32_t interval, void* param);
uint32_t hlp_SignalInputThread(uint32_t interval, void* param);
static void hlp_InitRenderTimer(void* ctrl);
static void hlp_InitInputTimer(void* ctrl);

/** @fn void timer_InitTimers(void* ctrl)
 * @brief This function initializes all timers relevant to running the engine.
 * 
 */
void timer_InitTimers(void* ctrl)
{

  // Create the needed mutexes.
  ((thread_vars_t*) ctrl)->mutexes[THREAD_RENDER]       = (SDL_CreateMutex());
  ((thread_vars_t*) ctrl)->mutexes[THREAD_INPUT]        = (SDL_CreateMutex());
  // Create the needed signals.
  ((thread_vars_t*) ctrl)->signal_update[THREAD_RENDER] = SDL_CreateCond();
  ((thread_vars_t*) ctrl)->signal_update[THREAD_INPUT]  = SDL_CreateCond();
  // Initialize the timers.
  hlp_InitRenderTimer(ctrl);
  hlp_InitInputTimer(ctrl);
} /* timer_InitTimers */

/** @fn void timer_KillTimers(std::vect<SDL_TimerID> ids)
 * @brief This function iterates through and kills timers held in a vector.
 * 
 * @param std::vector<SDL_TimerID>
 * IDs of the Timers to destroy.
 */
void timer_KillTimers(std::vector<SDL_TimerID> ids)
{
  for (auto id = ids.begin(); id < ids.end(); id++)
  {
    SDL_RemoveTimer(*id);
  }
} /* timer_KillTimers */

/** @fn static void hlp_InitRenderTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the rendering thread to run.
 * 
 * 
 * @return 0
 * Returns 0 if the timer fails to initialize.
 */
static void hlp_InitRenderTimer(void* ctrl)
{
  ((thread_vars_t*) ctrl)->timerIDs.push_back(SDL_AddTimer(16 /* 16.6 ms is 60 Hz*/, hlp_SignalRenderThread, ctrl));
} /* hlp_InitRenderTimer */

/** @fn static void hlp_InitInputTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the input thread to run.
 * 
 * @return 0
 * Returns 0 if the timer fails to initialize.
 */
static void hlp_InitInputTimer(void* ctrl)
{
  // On average 30 ping is pretty good so 10 ms delay should be unnoticable.
  ((thread_vars_t*) ctrl)->timerIDs.push_back(SDL_AddTimer(10, hlp_SignalInputThread, ctrl));
} /* hlp_InitInputTimer */

/** @fn uint32_t hlp_SignalRenderThread(uint32_t interval, void* param)
 * @brief This function is the call back function for the timers.
 * 
 * @param void*
 * A void pointer to a @ref thread_ctrl_t type
 */
uint32_t hlp_SignalRenderThread(uint32_t interval, void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;
  SDL_mutexP(ctrl->mutexes[THREAD_RENDER]);
  int status = SDL_CondSignal(ctrl->signal_update[THREAD_RENDER]);
  SDL_mutexV(ctrl->mutexes[THREAD_RENDER]);
  return interval;
} /* hlp_SignalRenderThread */

/** @fn uint32_t hlp_SignalInputThread(uint32_t interval, void* param)
 * @brief This function is the call back function for the timers.
 * 
 * @param void*
 * A void pointer to a @ref thread_ctrl_t type
 */
uint32_t hlp_SignalInputThread(uint32_t interval, void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;
  SDL_mutexP(ctrl->mutexes[THREAD_INPUT]);
  int status = SDL_CondSignal(ctrl->signal_update[THREAD_INPUT]);
  SDL_mutexV(ctrl->mutexes[THREAD_INPUT]);
  return interval;
} /* hlp_SignalInputThread */
