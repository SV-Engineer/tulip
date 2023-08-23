/** @file thread_ctrl.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for threading control..
 * 
 * @par This file contains the various types used for controlling threads.
 * 
 */

#ifndef TULIP_THREAD_CTRL_H_
  #define TULIP_THREAD_CTRL_H_

  #include <SDL.h>
  #include <SDL_thread.h>
  #include <vector>
  #include <map>
  #include <string>
  #include <renderer.hpp>
  #include <timers.hpp>
  #include <mouse_input.hpp>

  // Macros and Defines
  #define THREAD_RENDER         ((const std::string) "render")
  #define THREAD_INPUT          ((const std::string) "input")

  /** @brief This struct is used to organize the location the camera relative to the background. */
  typedef struct cam_coordinates
  {
    int x;
    int y;
    int prev_x {-1};
    int prev_y {-1};
  } cam_coordinates_t;

  /** @brief This struct is used to organize the various control mechanisms for threading. */
  typedef struct thread_vars
  {
    Screen*                            engine_window;
    std::map<std::string, SDL_cond*>   signal_update;
    std::map<std::string, SDL_mutex*>  mutexes;
    std::vector<SDL_TimerID>           timerIDs;
    SDL_sem*                           sem;
    bool                               kill;
    mouse_input_t                      mouse_loc;
    SDL_Keycode                        key_pressed;
    cam_coordinates_t                  coordinates;
    SDL_Event*                         e;
  } thread_vars_t;

  /** @brief This enumerate tracks all of the available threads. */
  enum thread_types
  {
    E_RENDER,
    E_KB_INPUT,
    E_NUM_THREADS
  };

  typedef thread_types thread_types_t;

  // Function declarations
  SDL_ThreadFunction thread_GetThreadPtr(thread_types_t t);

#endif /* TULIP_THREAD_CTRL_H_ */
