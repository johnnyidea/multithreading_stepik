# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2021.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2021.3.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rene/education/multithreading_stepik/socket_app/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_app.dir/flags.make

CMakeFiles/server_app.dir/server_app.cpp.o: CMakeFiles/server_app.dir/flags.make
CMakeFiles/server_app.dir/server_app.cpp.o: ../server_app.cpp
CMakeFiles/server_app.dir/server_app.cpp.o: CMakeFiles/server_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_app.dir/server_app.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_app.dir/server_app.cpp.o -MF CMakeFiles/server_app.dir/server_app.cpp.o.d -o CMakeFiles/server_app.dir/server_app.cpp.o -c /home/rene/education/multithreading_stepik/socket_app/server/server_app.cpp

CMakeFiles/server_app.dir/server_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_app.dir/server_app.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rene/education/multithreading_stepik/socket_app/server/server_app.cpp > CMakeFiles/server_app.dir/server_app.cpp.i

CMakeFiles/server_app.dir/server_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_app.dir/server_app.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rene/education/multithreading_stepik/socket_app/server/server_app.cpp -o CMakeFiles/server_app.dir/server_app.cpp.s

# Object files for target server_app
server_app_OBJECTS = \
"CMakeFiles/server_app.dir/server_app.cpp.o"

# External object files for target server_app
server_app_EXTERNAL_OBJECTS =

server_app: CMakeFiles/server_app.dir/server_app.cpp.o
server_app: CMakeFiles/server_app.dir/build.make
server_app: CMakeFiles/server_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_app.dir/build: server_app
.PHONY : CMakeFiles/server_app.dir/build

CMakeFiles/server_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_app.dir/clean

CMakeFiles/server_app.dir/depend:
	cd /home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rene/education/multithreading_stepik/socket_app/server /home/rene/education/multithreading_stepik/socket_app/server /home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug /home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug /home/rene/education/multithreading_stepik/socket_app/server/cmake-build-debug/CMakeFiles/server_app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_app.dir/depend

