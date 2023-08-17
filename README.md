# tulip
A 2-D game engine based upon SDL2. This attempt will try to incorporate the composition approach and may still use inheritance if and when it makes sense.

# Patch notes v0.0.1

## New Features
  1. Added direct3D 11 to the SDL initialization.

  2. Added tick timer.

  3. Added organization into threads.


# Patch notes v0.0.0

## New features
  1. Added all files for compilation of SDL2.

  2. Added makefile and ensured compilation.

  3. Added git ignore file (.gitignore) to avoid commiting object files to the repository.

  4. Added begginnings of doxygen automatic documentation generation.

  5. Added application control directory.
      * Rudimentary event handling.

  6. Added debug directory for debug macro definitions.

  7. Created a basic class wrapper for the SDL Window creation and handling. Initially the objects were created and passed to the class constructor. It made more sense to put the object instantation into the constructor and have a function that instantiated the class and did some error checking.

# Thoughts and TODOs
  * ~~The make file is really written only for facilitating unit tests and not releases~~.

  * The code in the compilation unit_test.cpp is taken verbatim from the [first lazyfoo SDL2 tutorial](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).

  * The documentation is not quite generating as expected. Need to refer to previous uses to see if there is something obvious I forgot.

  * TIL that initializing a struct with empty curly braces is a succinct way of guaranteeing all members are initialized to default values. I.e an 'int' type would be initialized to a value of `0` while a 'float' or 'double' will be initialized to a value of `0.0`.

  * Today I realized that I am still writing this with an embedded mindset. On a uController, when writing an interrupt driven system, sleeping is the way to save power. I believe my efforts to write threads have been hampered by this mindset. I think that instead of putting waits into the rendering thread, I need a "Tick" timer to send a signal to start and update every so often.
