# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/d/Study/Labs2course/DA_lab2/benchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_gprof.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_gprof.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_gprof.dir/flags.make

CMakeFiles/test_gprof.dir/test.cpp.o: CMakeFiles/test_gprof.dir/flags.make
CMakeFiles/test_gprof.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_gprof.dir/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_gprof.dir/test.cpp.o -c /mnt/d/Study/Labs2course/DA_lab2/benchmark/test.cpp

CMakeFiles/test_gprof.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gprof.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Study/Labs2course/DA_lab2/benchmark/test.cpp > CMakeFiles/test_gprof.dir/test.cpp.i

CMakeFiles/test_gprof.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gprof.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Study/Labs2course/DA_lab2/benchmark/test.cpp -o CMakeFiles/test_gprof.dir/test.cpp.s

CMakeFiles/test_gprof.dir/test.cpp.o.requires:

.PHONY : CMakeFiles/test_gprof.dir/test.cpp.o.requires

CMakeFiles/test_gprof.dir/test.cpp.o.provides: CMakeFiles/test_gprof.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_gprof.dir/build.make CMakeFiles/test_gprof.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/test_gprof.dir/test.cpp.o.provides

CMakeFiles/test_gprof.dir/test.cpp.o.provides.build: CMakeFiles/test_gprof.dir/test.cpp.o


# Object files for target test_gprof
test_gprof_OBJECTS = \
"CMakeFiles/test_gprof.dir/test.cpp.o"

# External object files for target test_gprof
test_gprof_EXTERNAL_OBJECTS =

test_gprof: CMakeFiles/test_gprof.dir/test.cpp.o
test_gprof: CMakeFiles/test_gprof.dir/build.make
test_gprof: CMakeFiles/test_gprof.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_gprof"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_gprof.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_gprof.dir/build: test_gprof

.PHONY : CMakeFiles/test_gprof.dir/build

CMakeFiles/test_gprof.dir/requires: CMakeFiles/test_gprof.dir/test.cpp.o.requires

.PHONY : CMakeFiles/test_gprof.dir/requires

CMakeFiles/test_gprof.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_gprof.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_gprof.dir/clean

CMakeFiles/test_gprof.dir/depend:
	cd /mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Study/Labs2course/DA_lab2/benchmark /mnt/d/Study/Labs2course/DA_lab2/benchmark /mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug /mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug /mnt/d/Study/Labs2course/DA_lab2/benchmark/cmake-build-debug/CMakeFiles/test_gprof.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_gprof.dir/depend

