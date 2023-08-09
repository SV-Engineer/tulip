/** @file debug.hpp
 * @author Autin (SV-Engineer)
 * @brief The header file for debugging macros.
 * 
 * @par This file contains macro definitions for debugging and logging to the console.
 * 
 */

#ifndef DEBUG_HPP_
  #define DEBUG_HPP_

  #define SUCCESS             0
  #define FAILURE            -1

  #ifdef DEBUG
      #include <string>
      #include <iostream>
      #define INFO(X)         std::cout << "*INFO: " #X << std::endl
      #define ERR(X,Y)        std::cout << "*ERR: "  #X << Y << std::endl
    #else
      #define INFO(X)
      #define ERR(X,Y)
    #endif

#endif /* DEBUG_HPP_ */
