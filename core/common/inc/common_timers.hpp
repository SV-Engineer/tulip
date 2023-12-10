/** @file common_threads.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for the Tulip threads template(s).
 * 
 * @par This file contains the definition of the thread template function(s).
 * 
 */

#ifndef COMMON_THREADS_H_
  #define COMMON_THREADS_H_

  #include <SDL.h>
  #include <debug.hpp>
  #include <string>

  #define SDL_NO_TIMER_ID_ERR ((SDL_TimerID) 0x0)

  enum
  {
    E_IDLE,
    E_INPUT,
    E_RENDER
  };

  uint32_t signal_thread(uint32_t interval, void* param);

  class Tulip_timer
  {
    public:
      //========================================================================
      // Public Member Variables
      //========================================================================
      SDL_TimerID Id;
      SDL_mutex*  Lock;
      SDL_cond*   Signal;

      //========================================================================
      // Public Member Functions
      //========================================================================
      // Constructor
      Tulip_timer(int duration_ms)
      {
        this->Lock           = SDL_CreateMutex();
        this->Signal         = SDL_CreateCond();
        Id                   = SDL_AddTimer(duration_ms, signal_thread, (void*) this);
      }

      // Destructor
    ~Tulip_timer(void)
      {
        SDL_RemoveTimer(Id);
        SDL_DestroyCond(this->Signal);
        SDL_DestroyMutex(this->Lock);
      }
  };

  uint32_t signal_thread(uint32_t interval, void* param)
  {

    #ifdef DEBUG
      INFO("Signalling Thread with timer:");
      std::cout << interval << std::endl;
    #endif

    Tulip_timer* tulip_timer = (Tulip_timer*) param;
    int status = 0;
    //thread_vars_t* ctrl = (thread_vars_t*) param;
    if (SDL_TryLockMutex (tulip_timer->Lock) == SUCCESS)
    {
      SDL_CondSignal(tulip_timer->Signal);
      SDL_UnlockMutex(tulip_timer->Lock);
      return interval;
    }
    else
    {
      return interval;
    }
  }

#endif /* COMMON_THREADS_H_ */
