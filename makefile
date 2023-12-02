############################################################################################
# Directory Variables
############################################################################################
CORE_DIR									= ./core
COMMON_DIR								= $(CORE_DIR)/common
UI_DIR										= ./user_interface
RENDER_DIR								= ./rendering
PHYSICS_DIR								= ./physics
OUTPUT_DIR								= ./obj
UNIT_TESTS_SRC_DIR				= ./unit_tests
DEBUG_DIR									= ./debug
SDL2_DIR									= $(CORE_DIR)/SDL2_Latest/i686-w64-mingw32

############################################################################################
# Source Paths
############################################################################################
UI_SRC										= $(UI_DIR)/src
RENDER_SRC								= $(RENDER_DIR)/src
PHYSICS_SRC								= $(PHYSICS_DIR)/src
COMMON_SRC								= $(COMMON_DIR)/src

############################################################################################
# Include Paths
############################################################################################
SDL2_INC									= $(SDL2_DIR)/include
UI_INC										= $(UI_DIR)/inc
RENDER_INC								= $(RENDER_DIR)/inc
PHYSICS_INC								= $(PHYSICS_DIR)/inc
COMMON_INC								= $(COMMON_DIR)/inc
DEBUG_INC									= $(DEBUG_DIR)/inc

############################################################################################
# Compiler Used
############################################################################################
CC												= g++

############################################################################################
# Compiler Arguments
############################################################################################
MAIN_CC_ARGS							= -std=c++17
CC_ARGS										= $(MAIN_CC_ARGS) -c -D DEBUG

############################################################################################
# Include Directory Compiler Arguments
############################################################################################
INC_DIRS									= -I $(SDL2_INC)/SDL2 \
														-I $(UI_INC)        \
														-I $(RENDER_INC)    \
														-I $(PHYSICS_INC)   \
														-I $(COMMON_INC)    \
														-I $(DEBUG_INC)

############################################################################################
# Link Directory Compiler Arguments
############################################################################################
LINK_DIRS									= -L $(SDL2_DIR)/bin/ \
														-L $(OUTPUT_DIR)

############################################################################################
# Link Library Compiler Arguments
############################################################################################
LINK_LIBS									= -l mingw32  \
														-l SDL2main \
														-l SDL2

############################################################################################
# Set argument variables (This makefile expects argument UT to provide a valid directory
# name from the unit_tests directory).
############################################################################################
UNIT_TEST = $(UT)

############################################################################################
# Dependencies list for compilation.
############################################################################################
UI_DEPS =				ui_events         \
								ui_keyboard_input \
								ui_mouse_input    \
								ui_threads        \
								ui_timers

RENDER_DEPS = 	rnd_threads       \
								rnd_timers

PHYSICS_DEPS =	phys_threads      \
								phys_timers

DEPS_LIST = 		$(UI_DEPS)        \
								$(RENDER_DEPS)    \
								$(PHYSICS_DEPS)

############################################################################################
# Expected object files from compilation to provide to linker.
############################################################################################
UI_OBJS		= 		$(OUTPUT_DIR)/ui_events.o         \
								$(OUTPUT_DIR)/ui_keyboard_input.o \
								$(OUTPUT_DIR)/ui_mouse_input.o    \
								$(OUTPUT_DIR)/ui_threads.o        \
								$(OUTPUT_DIR)/ui_timers.o

RENDER_OBJS = 	$(OUTPUT_DIR)/rnd_threads.o       \
								$(OUTPUT_DIR)/rnd_timers.o

PHYSICS_OBJS =	$(OUTPUT_DIR)/phys_threads.o      \
								$(OUTPUT_DIR)/phys_timers.o

OBJ_FILES =			$(UI_OBJS)                        \
								$(RENDER_OBJS)                    \
								$(PHYSICS_OBJS)

############################################################################################
# Compile the engine primary
############################################################################################
all: tulip engine

############################################################################################
# Compile the engine unit test
#   * mingw32-make test UT=compilation
#   * mingw32-make test UT=render
#   * mingw32-make test UT=draw_square
############################################################################################
test: unit_test engine

############################################################################################
# Dependency Recipes
############################################################################################

############################################################################################
# User Interface Recipes
############################################################################################\

ui_timers:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

ui_events:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

ui_mouse_input:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

ui_keyboard_input:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

ui_threads:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

############################################################################################
# Rendering Recipes
############################################################################################

rnd_threads:
	$(CC) $(CC_ARGS) $(RENDER_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

rnd_timers:
	$(CC) $(CC_ARGS) $(RENDER_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

############################################################################################
# Final Engine Recipes
############################################################################################
# This and the unit_test dependency are mutually exclusive in compilation.
tulip: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(COMMON_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

# Note that the object file this generates is the same name as the run_engine dependency.
unit_test: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(UNIT_TESTS_SRC_DIR)/$(UNIT_TEST)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/tulip.o

engine:
	$(CC) $(MAIN_CC_ARGS) $(CORE_DIR)/main.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) $(OBJ_FILES) -o $(OUTPUT_DIR)/$@.exe

clean:
	-rm ./obj/*.o ./obj/*.exe
