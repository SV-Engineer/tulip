# First setup the miscellaneous variables required for easy maintenance.
MAIN_SRC_DIR							= ./core
UNIT_TESTS_SRC_DIR				= ./unit_tests
OUTPUT_DIR								= ./obj

# Compiler used
CC												= g++

# Compiler arguments
CC_ARGS										= -c

# include directories
INC_DIRS									= ./core/SDL2_Latest/i686-w64-mingw32/include/SDL2 \
														./application_control/inc

# directory of libraries to link to
LINK_DIRS									= ./core/SDL2_Latest//i686-w64-mingw32/bin/

# directory of libraries to link to
LINK_LIBS									= -l mingw32 \
														-l SDL2main \
														-l SDL2

# Set argument variables (This make file expects argument
# UT to provide a valid directory name from the unit_tests
# directory).
UNIT_TEST = $(UT)

# Compile and output
all: engine.exe

events.o:
	$(CC) $(CC_ARGS) -I $(INC_DIRS) -L $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@

func.o:
	$(CC) $(CC_ARGS) -I $(INC_DIRS) -L $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@

engine.exe: events.o func.o
	$(CC) $(UNIT_TESTS_SRC_DIR)/$(UNIT_TEST)/unit_test.cpp $(MAIN_SRC_DIR)/main.cpp -I $(INC_DIRS) -L $(LINK_DIRS) $(LINK_LIBS) -o $(OUTPUT_DIR)/$@
