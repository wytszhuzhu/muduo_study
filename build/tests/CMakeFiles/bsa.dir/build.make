# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hugging/muduo_study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hugging/muduo_study/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/bsa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/bsa.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/bsa.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/bsa.dir/flags.make

tests/CMakeFiles/bsa.dir/bsa.cc.o: tests/CMakeFiles/bsa.dir/flags.make
tests/CMakeFiles/bsa.dir/bsa.cc.o: ../tests/bsa.cc
tests/CMakeFiles/bsa.dir/bsa.cc.o: tests/CMakeFiles/bsa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hugging/muduo_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/bsa.dir/bsa.cc.o"
	cd /home/hugging/muduo_study/build/tests && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/bsa.dir/bsa.cc.o -MF CMakeFiles/bsa.dir/bsa.cc.o.d -o CMakeFiles/bsa.dir/bsa.cc.o -c /home/hugging/muduo_study/tests/bsa.cc

tests/CMakeFiles/bsa.dir/bsa.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bsa.dir/bsa.cc.i"
	cd /home/hugging/muduo_study/build/tests && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hugging/muduo_study/tests/bsa.cc > CMakeFiles/bsa.dir/bsa.cc.i

tests/CMakeFiles/bsa.dir/bsa.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bsa.dir/bsa.cc.s"
	cd /home/hugging/muduo_study/build/tests && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hugging/muduo_study/tests/bsa.cc -o CMakeFiles/bsa.dir/bsa.cc.s

# Object files for target bsa
bsa_OBJECTS = \
"CMakeFiles/bsa.dir/bsa.cc.o"

# External object files for target bsa
bsa_EXTERNAL_OBJECTS =

bin/bsa: tests/CMakeFiles/bsa.dir/bsa.cc.o
bin/bsa: tests/CMakeFiles/bsa.dir/build.make
bin/bsa: tests/CMakeFiles/bsa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hugging/muduo_study/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/bsa"
	cd /home/hugging/muduo_study/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bsa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/bsa.dir/build: bin/bsa
.PHONY : tests/CMakeFiles/bsa.dir/build

tests/CMakeFiles/bsa.dir/clean:
	cd /home/hugging/muduo_study/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/bsa.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/bsa.dir/clean

tests/CMakeFiles/bsa.dir/depend:
	cd /home/hugging/muduo_study/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hugging/muduo_study /home/hugging/muduo_study/tests /home/hugging/muduo_study/build /home/hugging/muduo_study/build/tests /home/hugging/muduo_study/build/tests/CMakeFiles/bsa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/bsa.dir/depend

