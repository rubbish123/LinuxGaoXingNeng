# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/meandi/Linux高性能服务器编程

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/meandi/Linux高性能服务器编程/build

# Include any dependencies generated for this target.
include 8.高性能服务器程序框架/CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include 8.高性能服务器程序框架/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include 8.高性能服务器程序框架/CMakeFiles/main.dir/flags.make

8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.o: 8.高性能服务器程序框架/CMakeFiles/main.dir/flags.make
8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.o: ../8.高性能服务器程序框架/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/meandi/Linux高性能服务器编程/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.o"
	cd /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/main.cpp.o -c /home/meandi/Linux高性能服务器编程/8.高性能服务器程序框架/main.cpp

8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/meandi/Linux高性能服务器编程/8.高性能服务器程序框架/main.cpp > CMakeFiles/main.dir/main.cpp.i

8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/meandi/Linux高性能服务器编程/8.高性能服务器程序框架/main.cpp -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

8.高性能服务器程序框架/main: 8.高性能服务器程序框架/CMakeFiles/main.dir/main.cpp.o
8.高性能服务器程序框架/main: 8.高性能服务器程序框架/CMakeFiles/main.dir/build.make
8.高性能服务器程序框架/main: 8.高性能服务器程序框架/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/meandi/Linux高性能服务器编程/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
8.高性能服务器程序框架/CMakeFiles/main.dir/build: 8.高性能服务器程序框架/main

.PHONY : 8.高性能服务器程序框架/CMakeFiles/main.dir/build

8.高性能服务器程序框架/CMakeFiles/main.dir/clean:
	cd /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : 8.高性能服务器程序框架/CMakeFiles/main.dir/clean

8.高性能服务器程序框架/CMakeFiles/main.dir/depend:
	cd /home/meandi/Linux高性能服务器编程/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/meandi/Linux高性能服务器编程 /home/meandi/Linux高性能服务器编程/8.高性能服务器程序框架 /home/meandi/Linux高性能服务器编程/build /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架 /home/meandi/Linux高性能服务器编程/build/8.高性能服务器程序框架/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 8.高性能服务器程序框架/CMakeFiles/main.dir/depend

