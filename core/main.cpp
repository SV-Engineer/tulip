/** @author Autin (SV-Engineer)
 * @brief The main entry point.
 * 
 * @par This file contains the main entry point for the engine and will be used for testing purposes.
 * There is an expectation that a function pointer will be defined so as to be able to choose between
 * the main and unit tests.
 */

extern int (*func_ptr)(void);

/** @fn int main (void) 
 * @brief The main entry point.
 * 
 * @return Zero implies success and negative numbers imply error. Positive numbers imply warnings.
 */
int main (int argv, char** args)
{
 return func_ptr();
} /* main */
