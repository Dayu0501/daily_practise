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
CMAKE_SOURCE_DIR = /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build

# Include any dependencies generated for this target.
include src/CMakeFiles/myTest.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/myTest.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/myTest.dir/flags.make

src/CMakeFiles/myTest.dir/main.cpp.o: src/CMakeFiles/myTest.dir/flags.make
src/CMakeFiles/myTest.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/myTest.dir/main.cpp.o"
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myTest.dir/main.cpp.o -c /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/src/main.cpp

src/CMakeFiles/myTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myTest.dir/main.cpp.i"
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/src/main.cpp > CMakeFiles/myTest.dir/main.cpp.i

src/CMakeFiles/myTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myTest.dir/main.cpp.s"
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/src/main.cpp -o CMakeFiles/myTest.dir/main.cpp.s

src/CMakeFiles/myTest.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/myTest.dir/main.cpp.o.requires

src/CMakeFiles/myTest.dir/main.cpp.o.provides: src/CMakeFiles/myTest.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/myTest.dir/build.make src/CMakeFiles/myTest.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/myTest.dir/main.cpp.o.provides

src/CMakeFiles/myTest.dir/main.cpp.o.provides.build: src/CMakeFiles/myTest.dir/main.cpp.o


# Object files for target myTest
myTest_OBJECTS = \
"CMakeFiles/myTest.dir/main.cpp.o"

# External object files for target myTest
myTest_EXTERNAL_OBJECTS =

bin/myTest: src/CMakeFiles/myTest.dir/main.cpp.o
bin/myTest: src/CMakeFiles/myTest.dir/build.make
bin/myTest: lib/libTmath.so
bin/myTest: src/CMakeFiles/myTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/myTest"
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/myTest.dir/build: bin/myTest

.PHONY : src/CMakeFiles/myTest.dir/build

src/CMakeFiles/myTest.dir/requires: src/CMakeFiles/myTest.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/myTest.dir/requires

src/CMakeFiles/myTest.dir/clean:
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src && $(CMAKE_COMMAND) -P CMakeFiles/myTest.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/myTest.dir/clean

src/CMakeFiles/myTest.dir/depend:
	cd /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/src /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src /home/yulichao/code_code/daily_practice/daily_practise/cmake_learn/build/src/CMakeFiles/myTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/myTest.dir/depend

