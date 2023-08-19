/** @file run_engine.cpp
 * @author Autin (SV-Engineer)
 * @brief The source file for the main engine.
 * 
 * @par This file contains the source for the default compilation of the engine.
 * 
 */

#include <run_engine.hpp>

// Forward declare the unit test function.
int run_engine(void);

int (*func_ptr)(void) = &run_engine;

int run_engine(void)
{
  return SUCCESS;
}
