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
    private:
      SDL_mutex* lock;
      SDL_cond*  signal;

    public:
      //========================================================================
      // Public Member Variables
      //========================================================================
      SDL_TimerID Id;

      //========================================================================
      // Public Member Functions
      //========================================================================
      // Constructor
      Tulip_timer(int duration_ms)
      {
        this->lock           = SDL_CreateMutex();
        this->signal         = SDL_CreateCond();
        Id                   = SDL_AddTimer(duration_ms, signal_thread, (void*) this);
      } /* constructor */

      // Destructor
      ~Tulip_timer(void)
      {
        SDL_RemoveTimer(Id);
        SDL_DestroyCond(this->signal);
        SDL_DestroyMutex(this->lock);
      } /* destructor */

      int Try_get_lock(void)
      {
        return SDL_TryLockMutex(this->lock);
      } /* Try_get_lock */

      void Put_lock(void)
      {
        SDL_UnlockMutex(this->lock);
      } /* Put_lock */

      void Try_signal(void)
      {
        if (Try_get_lock() == SUCCESS)
        {
          SDL_CondSignal(this->signal);
          Put_lock();
          return;
        }
        else
        {
          return;
        }
      } /* Try_signal */

  };

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

#endif /* COMMON_THREADS_H_ */
