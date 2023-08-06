# First setup the miscellaneous variables required for easy maintenance.
CORE_DIR									= ./core
UNIT_TESTS_SRC_DIR				= ./unit_tests
OUTPUT_DIR								= ./obj
APP_CTRL_SRC							= ./application_control/src

# Compiler used
CC												= g++

# Compiler arguments
CC_ARGS										= -c

# include directories
INC_DIRS									= -I ./core/SDL2_Latest/i686-w64-mingw32/include/SDL2 \
														-I ./application_control/inc/

# directory of libraries to link to
LINK_DIRS									= -L ./core/SDL2_Latest/i686-w64-mingw32/bin/ \
														-L ./obj/

# directory of libraries to link to
LINK_LIBS									= -l mingw32 \
														-l SDL2main \
														-l SDL2

# Set argument variables (This make file expects argument
# UT to provide a valid directory name from the unit_tests
# directory).
UNIT_TEST = $(UT)

DEPS_LIST = renderer \
						events

OBJ_FILES = ./obj/renderer.o \
						./obj/events.o \
						./obj/run_engine.o

# Compile and output
all: run_engine engine

renderer:
	$(CC) $(CC_ARGS) $(APP_CTRL_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

events:
	$(CC) $(CC_ARGS) $(APP_CTRL_SRC)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

run_engine: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(CORE_DIR)/common/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@.o

all_unit_test: unit_test engine

unit_test: $(DEPS_LIST)
	$(CC) $(CC_ARGS) $(UNIT_TESTS_SRC_DIR)/$(UNIT_TEST)/$@.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/run_engine.o

engine: 
	$(CC) $(CORE_DIR)/main.cpp $(INC_DIRS) $(LINK_DIRS) $(LINK_LIBS) $(OBJ_FILES) -o $(OUTPUT_DIR)/$@.exe

clean:
	-rm ./obj/*.o ./obj/engine.exe
