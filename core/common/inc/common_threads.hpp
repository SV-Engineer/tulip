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

  template <class T> class Tulip_timer
  {
    public:
      // Constructor
      template <class T> class Tulip_timer(std::string name = "")
      {
        this.timer_name     = name;
        this.Lock           = SDL_CreateMutex();
        this._thread_signal = SDL_CreateCond();
      }

      std::string timer_name;
      SDL_TimerID Id;
      SDL_mutex*  Lock;

      ~ template <class T> class Tulip_timer(std::string name = "")
      {
        
      }


    private:
      SDL_cond*  _thread_signal;
      uint32_t signal_thread(uint32_t interval, void* param)
      {
        int status = 0;
        //thread_vars_t* ctrl = (thread_vars_t*) param;
        if (SDL_LockMutex (this->Lock) == SUCCESS)
        {
          SDL_CondSignal(this->_thread_signal);
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