/** @file common_timers.hpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the Tulip generic timers.
 * 
 * @par This file contains the definition of the generic timer.
 * 
 */

#include "common_timers.hpp"

/** @fn uint32_t signal_thread (uint32_t interval, void* param)
 * @brief This function is the call back function of the timers that signals the thread associated with said timer.
 * 
 * @return uint32_t
 * The duration of the next timer run.
 */
uint32_t signal_thread(uint32_t interval, void* param)
{

  #ifdef DEBUG
    INFO("Signalling Thread with timer:");
    std::cout << interval << std::endl;
  #endif

  Tulip_timer* tulip_timer = (Tulip_timer*) param;

  tulip_timer->Try_signal();

  return interval;
} /* signal_thread */

/** @fn void timers_kill_timers (Timers_vect_t* timers)
 * @brief This calls the destructor of the timers stored within the vector.
 * 
 * @par The destructors for the heap allocated timer classes are called here.
 * Upon destroying all associated objects, the container the pointers lived in
 * is then destroyed as well.
 * 
 * @return void
 *
 */
void timers_kill_timers (Timers_t* timers)
{
  for (auto iter = timers->begin(); iter != timers->end(); iter++)
  {
    // The timer class instance is the second entry.
    delete iter->second;
  }
}
