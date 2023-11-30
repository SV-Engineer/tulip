# tulip
A 2-D game engine based upon SDL2. This attempt will try to incorporate the composition approach and may still use inheritance if and when it makes sense.

# Patch notes v0.0.2

## New Features
  1. Added visio drawings (this doesn't quite work with git; I forgot git doesn't like binary files and I will figure something out).

  2. Reorganized rendering into it's own module. Note that the threading portion of the user interface module has dependency on this, will likely need to decouple.

  3. Changed Application Control to "user_interface" so as to more easily granularize the different modules and thus know where each submodule goes.

  4. Hot-patches.
      1. v0.0.2.1 - Removed visio file. It now lives on [google drive](https://drive.google.com/drive/folders/1e4nrK_8WwpWtN2_9AYjk2QZC2V8AnO7W?usp=sharing) in the "Drawings" folder.

## Known Issues.
  * Most unit tests are broken. Expect hot-patch to fix.

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

  * The timer call back function needs to return the "interval" input to restart the timer. So the requirements and steps to put rendering into its own thread and decouple it from the rest of the logic is as follows:
    - Requirements
      * A boolean pointer and associated semaphore for interprocess communication of when to quit. (It may be that the Semaphore could be a mutex, but I have thoughts on why it should be a semaphore that I can't quite articulate right now).
      * A condition variable and an associated mutex so that the rendering thread can be "put to sleep" until the rendering timer signals it to start back up.

    - Steps:
      1. Create the aforementioned objects.

      2. Create a thread for rendering that is dependent upon the condition variable being signaled.

      3. Detach created thread because rendering should (probably) be independent of the engine logic. Also we don't want hang ups in the event polling if it can be helped.

      4. Create the timer that causes rendering to happen.

      5. Poll for the quit event and update the boolean pointer appropriately. The render thread should have a while loop based upon said boolean.

      6. Keep rendering until exit. Upon exit deallocate any memory used.
