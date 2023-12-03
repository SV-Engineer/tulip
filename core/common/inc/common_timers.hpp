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

  #define SDL_NO_TIMER_ID_ERR ((SDL_TimerID) 0x0)

  enum
  {
    E_IDLE,
    E_INPUT,
    E_RENDER
  };

  template <class T> class Tulip_timer
  {
    public:
      //========================================================================
      // Public Member Variables
      //========================================================================
      std::string timer_name;
      SDL_TimerID Id;
      SDL_mutex*  Lock;
      SDL_cond*   signal_thread;

      //========================================================================
      // Public Member Functions
      //========================================================================
      // Constructor
      Tulip_timer(std::string name = "", int duration_ms, void* params)
      {
        this.timer_name      = name;
        this->Lock           = SDL_CreateMutex();
        this->signal_thread  = SDL_CreateCond();
        this.Id              = SDL_AddTimer(duration_ms, this.hlp_signal_thread, params);
      }

      // Destructor
      ~Tulip_timer(void)
      {
        SDL_RemoveTimer(this.Id);
        SDL_DestroyCond(this->signal_thread);
        SDL_DestroyMutex(this->Lock);
      }

    private:
      //========================================================================
      // Private Functions
      //========================================================================
      uint32_t hlp_signal_thread(uint32_t interval, void* param)
      {
        int status = 0;
        //thread_vars_t* ctrl = (thread_vars_t*) param;
        if (SDL_TryLockMutex (this->Lock) == SUCCESS)
        {
          SDL_CondSignal(this->signal_thread);
          SDL_UnlockMutex(this->Lock);
          return interval;
        }
        else
        {
          return interval;
        }
      }
  };

#endif /* COMMON_THREADS_H_ */
