/** @file events.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for tulip event handling.
 * 
 * @par This file contains the event handling for the tulip game engine.
 * At this time for sanity checking purposes it serves to create and event
 * and also poll it to check for the quit request.
 * 
 */

#include <events.hpp>

/** @fn SDL_Event* CreateEvent(void)
 * @brief This instantiates and returns a pointer to a heap allocated event.
 * 
 * @return SDL_Event
 * A pointer to a heap allocated event.
 */
SDL_Event* CreateEvent(void)
{
  SDL_Event* event = new SDL_Event();
  return event;
} /* CreateEvent */

/** @fn bool PollEvent(SDL_Event* e)
 * @brief This polls an event and deletes it off the heap upon quit request.
 * 
 * @return true
 * terminate program
 * 
 * @return false
 * do not terminate program
 */
bool PollEvent(SDL_Event* e)
{
  bool quit = false;

  while(SDL_PollEvent(e))
  {
    switch (e->type)
    {
      case(SDL_QUIT):
        quit = true;
        // Deallocate object from the heap
        delete e;
        break;

      default:
        break;
    }
  }

  return quit;
} /* PollEvent */
