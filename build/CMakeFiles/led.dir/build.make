# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ethan/Projects/led/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ethan/Projects/led/build

# Include any dependencies generated for this target.
include CMakeFiles/led.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/led.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/led.dir/flags.make

CMakeFiles/led.dir/led/main.c.o: CMakeFiles/led.dir/flags.make
CMakeFiles/led.dir/led/main.c.o: /home/ethan/Projects/led/src/led/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ethan/Projects/led/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/led.dir/led/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/led.dir/led/main.c.o   -c /home/ethan/Projects/led/src/led/main.c

CMakeFiles/led.dir/led/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/led.dir/led/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ethan/Projects/led/src/led/main.c > CMakeFiles/led.dir/led/main.c.i

CMakeFiles/led.dir/led/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/led.dir/led/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ethan/Projects/led/src/led/main.c -o CMakeFiles/led.dir/led/main.c.s

# Object files for target led
led_OBJECTS = \
"CMakeFiles/led.dir/led/main.c.o"

# External object files for target led
led_EXTERNAL_OBJECTS =

led: CMakeFiles/led.dir/led/main.c.o
led: CMakeFiles/led.dir/build.make
led: /home/ethan/Projects/led/src/../lib/libfrutti2d.so
led: /usr/lib/x86_64-linux-gnu/libOpenGL.so
led: /usr/lib/x86_64-linux-gnu/libGLX.so
led: /usr/lib/x86_64-linux-gnu/libGLU.so
led: /usr/lib/x86_64-linux-gnu/libGLEW.so
led: CMakeFiles/led.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ethan/Projects/led/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable led"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/led.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/led.dir/build: led

.PHONY : CMakeFiles/led.dir/build

CMakeFiles/led.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/led.dir/cmake_clean.cmake
.PHONY : CMakeFiles/led.dir/clean

CMakeFiles/led.dir/depend:
	cd /home/ethan/Projects/led/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ethan/Projects/led/src /home/ethan/Projects/led/src /home/ethan/Projects/led/build /home/ethan/Projects/led/build /home/ethan/Projects/led/build/CMakeFiles/led.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/led.dir/depend

