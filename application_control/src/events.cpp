/** @file events.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip event handling.
 * 
 * @par This file contains the event handling for the tulip game engine.
 * At this time for sanity checking purposes it serves to create an event
 * and also poll it to check for the quit request.
 * 
 */

#include <events.hpp>

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

/** @fn bool evt_PollEvent(SDL_Event* e)
 * @brief This polls an event and deletes it off the heap upon quit request.
 * 
 * @return true
 * terminate program
 * 
 * @return false
 * do not terminate program
 */
bool evt_PollEvent(SDL_Event* e)
{
  bool quit = false;

  while(SDL_PollEvent(e))
  {
    switch (e->type)
    {
      case(SDL_QUIT):
        quit = true;
        hlp_KillEvent(e);
        break;

      default:
        break;
    }
  }

  return quit;
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
