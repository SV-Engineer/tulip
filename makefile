############################################################################################
# Directory Variables
############################################################################################
CORE_DIR									= ./core
COMMON_DIR								= $(CORE_DIR)/common
UI_DIR										= ./user_interface
OUTPUT_DIR								= ./obj
UNIT_TESTS_SRC_DIR				= ./unit_tests
DEBUG_DIR									= ./debug
SDL2_DIR									= $(CORE_DIR)/SDL2_Latest/i686-w64-mingw32

############################################################################################
# Source Paths
############################################################################################
UI_SRC										= $(UI_DIR)/src
COMMON_SRC								= $(COMMON_DIR)/src

############################################################################################
# Include Paths
############################################################################################
SDL2_INC									= $(SDL2_DIR)/include
UI_INC										= $(UI_DIR)/inc
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
DEPS_LIST = renderer    \
						events      \
						timers      \
						thread_ctrl \
						mouse_input

############################################################################################
# Expected object files from compilation to provide to linker.
############################################################################################
OBJ_FILES = $(OUTPUT_DIR)/renderer.o    \
						$(OUTPUT_DIR)/events.o      \
						$(OUTPUT_DIR)/timers.o      \
						$(OUTPUT_DIR)/thread_ctrl.o \
						$(OUTPUT_DIR)/mouse_input.o \
						$(OUTPUT_DIR)/run_engine.o

############################################################################################
# Compile the engine primary
############################################################################################
all: run_engine engine

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
timers:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

renderer:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

events:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

mouse_input:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

thread_ctrl:
	$(CC) $(CC_ARGS) $(UI_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

# This and the unit_test dependency are mutually exclusive in compilation.
run_engine: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(COMMON_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

# Note that the object file this generates is the same as the run_engine dependency.
unit_test: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(UNIT_TESTS_SRC_DIR)/$(UNIT_TEST)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/run_engine.o

engine:
	$(CC) $(MAIN_CC_ARGS) $(CORE_DIR)/main.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) $(OBJ_FILES) -o $(OUTPUT_DIR)/$@.exe

clean:
	-rm ./obj/*.o ./obj/*.exe
