# tulip
A 2-D game engine based upon SDL2. This attempt will try to incorporate the composition approach and may still use inheritance if and when it makes sense.

# Patch notes v0p0

## New features
  1. Added all files for compilation of SDL2.

  2. Added makefile and ensured compilation.

  3. Added git ignore file (.gitignore) to avoid commiting object files to the repository.

  4. Added begginnings of doxygen automatic documentation generation.

  5. Added application control directory.
      * Rudimentary event handling.

  6. Added debug directory for debug macro definitions.

  7. Created a basic class wrapper for the SDL Window creation and handling. Initially the objects were created and passed to the class constructor. It made more sense to put the object instantation into the constructor and have a function that instantiated the class and did some error checking.

## Thoughts and TODOs
  * ~~The make file is really written only for facilitating unit tests and not releases~~.

  * The code in the compilation unit_test.cpp is taken verbatim from the [first lazyfoo SDL2 tutorial](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).

  * The documentation is not quite generating as expected. Need to refer to previous uses to see if there is something obvious I forgot.
