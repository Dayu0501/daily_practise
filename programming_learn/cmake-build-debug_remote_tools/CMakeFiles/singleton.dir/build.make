# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /tmp/tmp.eb0FULKHKg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools

# Include any dependencies generated for this target.
include CMakeFiles/singleton.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/singleton.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/singleton.dir/flags.make

CMakeFiles/singleton.dir/singleton.cpp.o: CMakeFiles/singleton.dir/flags.make
CMakeFiles/singleton.dir/singleton.cpp.o: ../singleton.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/singleton.dir/singleton.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/singleton.dir/singleton.cpp.o -c /tmp/tmp.eb0FULKHKg/singleton.cpp

CMakeFiles/singleton.dir/singleton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/singleton.dir/singleton.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.eb0FULKHKg/singleton.cpp > CMakeFiles/singleton.dir/singleton.cpp.i

CMakeFiles/singleton.dir/singleton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/singleton.dir/singleton.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.eb0FULKHKg/singleton.cpp -o CMakeFiles/singleton.dir/singleton.cpp.s

CMakeFiles/singleton.dir/singleton.cpp.o.requires:

.PHONY : CMakeFiles/singleton.dir/singleton.cpp.o.requires

CMakeFiles/singleton.dir/singleton.cpp.o.provides: CMakeFiles/singleton.dir/singleton.cpp.o.requires
	$(MAKE) -f CMakeFiles/singleton.dir/build.make CMakeFiles/singleton.dir/singleton.cpp.o.provides.build
.PHONY : CMakeFiles/singleton.dir/singleton.cpp.o.provides

CMakeFiles/singleton.dir/singleton.cpp.o.provides.build: CMakeFiles/singleton.dir/singleton.cpp.o


# Object files for target singleton
singleton_OBJECTS = \
"CMakeFiles/singleton.dir/singleton.cpp.o"

# External object files for target singleton
singleton_EXTERNAL_OBJECTS =

singleton: CMakeFiles/singleton.dir/singleton.cpp.o
singleton: CMakeFiles/singleton.dir/build.make
singleton: CMakeFiles/singleton.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable singleton"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/singleton.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/singleton.dir/build: singleton

.PHONY : CMakeFiles/singleton.dir/build

CMakeFiles/singleton.dir/requires: CMakeFiles/singleton.dir/singleton.cpp.o.requires

.PHONY : CMakeFiles/singleton.dir/requires

CMakeFiles/singleton.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/singleton.dir/cmake_clean.cmake
.PHONY : CMakeFiles/singleton.dir/clean

CMakeFiles/singleton.dir/depend:
	cd /tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.eb0FULKHKg /tmp/tmp.eb0FULKHKg /tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools /tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools /tmp/tmp.eb0FULKHKg/cmake-build-debug_remote_tools/CMakeFiles/singleton.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/singleton.dir/depend

