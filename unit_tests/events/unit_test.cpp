/** @file events/unit_test.cpp
 * @author Autin (SV-Engineer)
 * @brief The unit test for events.
 * 
 * @par This file contains the unit test used to sanity check the event control logic in the application control module.
 * To compile:
 *    1. Change directory to the top level (probably TULIP), but if not, whatever directory contains the makefile
 *    2. Use command:
 *        > mingw32-make makefile all UT=events
 */

#include <events.hpp>

// Forward declare the unit test function.
int unit_test(void);

int (*func_ptr)(void) = &unit_test;

int unit_test(void)
{

}
