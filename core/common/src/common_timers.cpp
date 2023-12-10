/** @file common_timers.hpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the Tulip generic timers.
 * 
 * @par This file contains the definition of the generic timer.
 * 
 */

#include "common_timers.hpp"

uint32_t signal_thread(uint32_t interval, void* param)
{

  #ifdef DEBUG
    INFO("Signalling Thread with timer:");
    std::cout << interval << std::endl;
  #endif

  Tulip_timer* tulip_timer = (Tulip_timer*) param;

  tulip_timer->Try_signal();

  return interval;
}
