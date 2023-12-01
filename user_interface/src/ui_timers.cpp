/** @file ui_timers.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip timers.
 * 
 * @par This file contains the source for the creating, using, and destroying timers.
 * 
 */

#include <ui_timers.hpp>

// Forward declare helper functions
uint32_t hlp_SignalRenderThread(uint32_t interval, void* param);
uint32_t hlp_SignalInputThread(uint32_t interval, void* param);
uint32_t hlp_SignalEventThread(uint32_t interval, void* param);

static void hlp_InitRenderTimer(void*);
static void hlp_InitInputTimer(void*);
static void hlp_InitEventTimer(void*);

/** @fn void timer_InitTimers(void* ctrl)
 * @brief This function initializes all timers relevant to running the engine.
 * 
 */
void timer_InitTimers(void* params, uint32_t timer_pos = 0xFFFFFFFFU)
{
  thread_vars_t* ctrl = (thread_vars_t*) params;

  // Create the needed mutexes.
  ctrl->mutexes[THREAD_RENDER]       = (timer_pos & (0x1U << E_RENDER)) ? SDL_CreateMutex() : nullptr;
  ctrl->mutexes[THREAD_INPUT]        = (timer_pos & (0x1U << E_INPUT))  ? SDL_CreateMutex() : nullptr;
  ctrl->mutexes[THREAD_IDLE]         = (timer_pos & (0x1U << E_IDLE))   ? SDL_CreateMutex() : nullptr;

  // Create the needed signals.
  ctrl->signal_update[THREAD_RENDER] = (timer_pos & (0x1U << E_RENDER)) ? SDL_CreateCond()  : nullptr;
  ctrl->signal_update[THREAD_INPUT]  = (timer_pos & (0x1U << E_INPUT))  ? SDL_CreateCond()  : nullptr;
  ctrl->signal_update[THREAD_IDLE]   = (timer_pos & (0x1U << E_IDLE))   ? SDL_CreateCond()  : nullptr;
  // Initialize the timers.
  hlp_InitRenderTimer(ctrl);
  hlp_InitInputTimer(ctrl);
  hlp_InitEventTimer(ctrl);
} /* timer_InitTimers */

/** @fn void timer_KillTimers(std::vect<SDL_TimerID> ids)
 * @brief This function iterates through and kills timers held in a vector.
 * 
 * @param std::vector<SDL_TimerID>
 * IDs of the Timers to destroy.
 */
void timer_KillTimers(void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;

  // for (auto i = ctrl->mutexes.begin(); i < ctrl->mutexes.end(); i++)
  // {

  // }
  SDL_mutexP(ctrl->mutexes[THREAD_RENDER]);
  SDL_mutexP(ctrl->mutexes[THREAD_INPUT]);
  SDL_mutexP(ctrl->mutexes[THREAD_IDLE]);
  for (auto id = ctrl->timerIDs.begin(); id < ctrl->timerIDs.end(); id++)
  {
    SDL_RemoveTimer(*id);
  }

  // TODO: Replace with for each loop.
  SDL_DestroyMutex(ctrl->mutexes[THREAD_RENDER]);
  SDL_DestroyMutex(ctrl->mutexes[THREAD_INPUT]);
  SDL_DestroyMutex(ctrl->mutexes[THREAD_IDLE]);

  SDL_DestroyCond(ctrl->signal_update[THREAD_RENDER]);
  SDL_DestroyCond(ctrl->signal_update[THREAD_INPUT]);
  SDL_DestroyCond(ctrl->signal_update[THREAD_IDLE]);
} /* timer_KillTimers */

/** @fn static void hlp_InitRenderTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the rendering thread to run.
 * 
 */
static void hlp_InitRenderTimer(void* params)
{
  thread_vars_t* ctrl = (thread_vars_t*) params;
  const std::string C_THREAD_NAME = THREAD_RENDER;
  if ((ctrl->mutexes[C_THREAD_NAME] != nullptr) && (ctrl->signal_update[C_THREAD_NAME] != nullptr));
  {
    ctrl->timerIDs.push_back(SDL_AddTimer(16 /* 16.6 ms is 60 Hz*/, hlp_SignalRenderThread, (void*) ctrl));
    return;
  }
  else
  {
    return;
  }
} /* hlp_InitRenderTimer */

/** @fn static void hlp_InitInputTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the input thread to run.
 * 
 */
static void hlp_InitInputTimer(void* ctrl)
{
  ((thread_vars_t*) ctrl)->timerIDs.push_back(SDL_AddTimer(10, hlp_SignalInputThread, ctrl));
} /* hlp_InitInputTimer */


/** @fn static void hlp_InitEventTimer(void* ctrl)
 * @brief This function instantiates a timer used to signal the event polling thread to run.
 * 
 */
static void hlp_InitEventTimer(void* ctrl)
{
  ((thread_vars_t*) ctrl)->timerIDs.push_back(SDL_AddTimer(1 /* Poll for events every 1 ms */, hlp_SignalEventThread, ctrl));
} /* hlp_InitEventTimer */

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

/** @fn uint32_t hlp_SignalEventThread(uint32_t interval, void* param)
 * @brief This function is the call back function for the timers.
 * 
 * @param void*
 * A void pointer to a @ref thread_ctrl_t type
 */
uint32_t hlp_SignalEventThread(uint32_t interval, void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;
  SDL_mutexP(ctrl->mutexes[THREAD_IDLE]);
  int status = SDL_CondSignal(ctrl->signal_update[THREAD_IDLE]);
  SDL_mutexV(ctrl->mutexes[THREAD_IDLE]);
  return interval;
} /* hlp_SignalEventThread */