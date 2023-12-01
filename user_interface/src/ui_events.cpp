/** @file ui_events.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip user interface event handling.
 * 
 * @par This file contains the UI event handling for the tulip game engine.
 * At this time for sanity checking purposes it serves to create an event
 * and also poll it to check for the quit request.
 * 
 */

#include <ui_events.hpp>

// Helper function forward declaration.
static inline void hlp_KillEvent(SDL_Event* e);

/** @fn SDL_Event* evt_CreateEvent(void)
 * @brief This instantiates and returns a pointer to a heap allocated event.
 * 
 * @return SDL_Event
 * A pointer to a heap allocated event.
 */
SDL_Event* evt_CreateEvent(void)
{
  SDL_Event* event = new SDL_Event();
  return event;
} /* evt_CreateEvent */

/** @fn void evt_PollEvent(SDL_Event* e, thread_vars_t* ctrl)
 * @brief This polls an event and deletes it off the heap upon quit request.
 * 
 * @return true
 * terminate program
 * 
 * @return false
 * do not terminate program
 */
void evt_PollEvent(void* param)
{
  thread_vars_t* ctrl = (thread_vars_t*) param;
  while(SDL_PollEvent(ctrl->e))
  {
    switch (ctrl->e->type)
    {
      case(SDL_QUIT):
        INFO("Kill Event Detected");
        ctrl->kill = true;
        hlp_KillEvent(ctrl->e);
        break;

      case(SDL_MOUSEMOTION):
        ctrl->mouse_loc = mouse_GetLocation();
        INFO("Mouse Moved");
        break;

      case(SDL_MOUSEBUTTONDOWN):
        ctrl->mouse_loc = mouse_GetLocation();
        INFO("Mouse button down");
        break;

      case(SDL_MOUSEBUTTONUP):
        ctrl->mouse_loc = mouse_GetLocation();
        INFO("Mouse button up");
        break;

      case(SDL_KEYDOWN):
        INFO("Key down");
        ctrl->key_pressed = ctrl->e->key.keysym.sym;
        break;

      case(SDL_KEYUP):
        INFO("Key up");
        break;

      default:
        break;
    }
  }
} /* evt_PollEvent */

// ===================================================================================
// Static helper functions
// ===================================================================================

/** @fn static inline SDL_Event* hlp_KillEvent(void)
 * @brief This instantiates and returns a pointer to a heap allocated event.
 * 
 * @param SDL_Event
 * A pointer to a heap allocated event.
 */
static inline void hlp_KillEvent(SDL_Event* e)
{
  // Deallocate object from the heap
  delete e;
} /* hlp_KillEvent */
