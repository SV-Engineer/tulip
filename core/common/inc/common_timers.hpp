/** @file common_timers.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for the Tulip generic timers.
 * 
 * @par This file contains the definition of the timers that will signal the threads.
 * 
 */

#ifndef COMMON_TIMERS_H_
  #define COMMON_TIMERS_H_

  #include <SDL.h>
  #include <debug.hpp>
  #include <string>
  #include <map>

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

  }; /* Tulip_timer */

  // Used to track the class handles
  typedef std::map <std::string, Tulip_timer*> Timers_t;

  // Function Declarations
  void timers_kill_timers (Timers_t*);

#endif /* COMMON_TIMERS_H_ */
