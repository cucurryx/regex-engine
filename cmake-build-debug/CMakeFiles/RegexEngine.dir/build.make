# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/xvvx/CLion-2017.3.4/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/xvvx/CLion-2017.3.4/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xvvx/code/RegexEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xvvx/code/RegexEngine/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RegexEngine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RegexEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RegexEngine.dir/flags.make

CMakeFiles/RegexEngine.dir/main.cc.o: CMakeFiles/RegexEngine.dir/flags.make
CMakeFiles/RegexEngine.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RegexEngine.dir/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RegexEngine.dir/main.cc.o -c /home/xvvx/code/RegexEngine/main.cc

CMakeFiles/RegexEngine.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexEngine.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xvvx/code/RegexEngine/main.cc > CMakeFiles/RegexEngine.dir/main.cc.i

CMakeFiles/RegexEngine.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexEngine.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xvvx/code/RegexEngine/main.cc -o CMakeFiles/RegexEngine.dir/main.cc.s

CMakeFiles/RegexEngine.dir/main.cc.o.requires:

.PHONY : CMakeFiles/RegexEngine.dir/main.cc.o.requires

CMakeFiles/RegexEngine.dir/main.cc.o.provides: CMakeFiles/RegexEngine.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/RegexEngine.dir/build.make CMakeFiles/RegexEngine.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/RegexEngine.dir/main.cc.o.provides

CMakeFiles/RegexEngine.dir/main.cc.o.provides.build: CMakeFiles/RegexEngine.dir/main.cc.o


CMakeFiles/RegexEngine.dir/nfa.cc.o: CMakeFiles/RegexEngine.dir/flags.make
CMakeFiles/RegexEngine.dir/nfa.cc.o: ../nfa.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RegexEngine.dir/nfa.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RegexEngine.dir/nfa.cc.o -c /home/xvvx/code/RegexEngine/nfa.cc

CMakeFiles/RegexEngine.dir/nfa.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexEngine.dir/nfa.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xvvx/code/RegexEngine/nfa.cc > CMakeFiles/RegexEngine.dir/nfa.cc.i

CMakeFiles/RegexEngine.dir/nfa.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexEngine.dir/nfa.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xvvx/code/RegexEngine/nfa.cc -o CMakeFiles/RegexEngine.dir/nfa.cc.s

CMakeFiles/RegexEngine.dir/nfa.cc.o.requires:

.PHONY : CMakeFiles/RegexEngine.dir/nfa.cc.o.requires

CMakeFiles/RegexEngine.dir/nfa.cc.o.provides: CMakeFiles/RegexEngine.dir/nfa.cc.o.requires
	$(MAKE) -f CMakeFiles/RegexEngine.dir/build.make CMakeFiles/RegexEngine.dir/nfa.cc.o.provides.build
.PHONY : CMakeFiles/RegexEngine.dir/nfa.cc.o.provides

CMakeFiles/RegexEngine.dir/nfa.cc.o.provides.build: CMakeFiles/RegexEngine.dir/nfa.cc.o


CMakeFiles/RegexEngine.dir/regex_parser.cc.o: CMakeFiles/RegexEngine.dir/flags.make
CMakeFiles/RegexEngine.dir/regex_parser.cc.o: ../regex_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RegexEngine.dir/regex_parser.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RegexEngine.dir/regex_parser.cc.o -c /home/xvvx/code/RegexEngine/regex_parser.cc

CMakeFiles/RegexEngine.dir/regex_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexEngine.dir/regex_parser.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xvvx/code/RegexEngine/regex_parser.cc > CMakeFiles/RegexEngine.dir/regex_parser.cc.i

CMakeFiles/RegexEngine.dir/regex_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexEngine.dir/regex_parser.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xvvx/code/RegexEngine/regex_parser.cc -o CMakeFiles/RegexEngine.dir/regex_parser.cc.s

CMakeFiles/RegexEngine.dir/regex_parser.cc.o.requires:

.PHONY : CMakeFiles/RegexEngine.dir/regex_parser.cc.o.requires

CMakeFiles/RegexEngine.dir/regex_parser.cc.o.provides: CMakeFiles/RegexEngine.dir/regex_parser.cc.o.requires
	$(MAKE) -f CMakeFiles/RegexEngine.dir/build.make CMakeFiles/RegexEngine.dir/regex_parser.cc.o.provides.build
.PHONY : CMakeFiles/RegexEngine.dir/regex_parser.cc.o.provides

CMakeFiles/RegexEngine.dir/regex_parser.cc.o.provides.build: CMakeFiles/RegexEngine.dir/regex_parser.cc.o


CMakeFiles/RegexEngine.dir/test.cc.o: CMakeFiles/RegexEngine.dir/flags.make
CMakeFiles/RegexEngine.dir/test.cc.o: ../test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RegexEngine.dir/test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RegexEngine.dir/test.cc.o -c /home/xvvx/code/RegexEngine/test.cc

CMakeFiles/RegexEngine.dir/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexEngine.dir/test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xvvx/code/RegexEngine/test.cc > CMakeFiles/RegexEngine.dir/test.cc.i

CMakeFiles/RegexEngine.dir/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexEngine.dir/test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xvvx/code/RegexEngine/test.cc -o CMakeFiles/RegexEngine.dir/test.cc.s

CMakeFiles/RegexEngine.dir/test.cc.o.requires:

.PHONY : CMakeFiles/RegexEngine.dir/test.cc.o.requires

CMakeFiles/RegexEngine.dir/test.cc.o.provides: CMakeFiles/RegexEngine.dir/test.cc.o.requires
	$(MAKE) -f CMakeFiles/RegexEngine.dir/build.make CMakeFiles/RegexEngine.dir/test.cc.o.provides.build
.PHONY : CMakeFiles/RegexEngine.dir/test.cc.o.provides

CMakeFiles/RegexEngine.dir/test.cc.o.provides.build: CMakeFiles/RegexEngine.dir/test.cc.o


CMakeFiles/RegexEngine.dir/dfa.cc.o: CMakeFiles/RegexEngine.dir/flags.make
CMakeFiles/RegexEngine.dir/dfa.cc.o: ../dfa.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RegexEngine.dir/dfa.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RegexEngine.dir/dfa.cc.o -c /home/xvvx/code/RegexEngine/dfa.cc

CMakeFiles/RegexEngine.dir/dfa.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexEngine.dir/dfa.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xvvx/code/RegexEngine/dfa.cc > CMakeFiles/RegexEngine.dir/dfa.cc.i

CMakeFiles/RegexEngine.dir/dfa.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexEngine.dir/dfa.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xvvx/code/RegexEngine/dfa.cc -o CMakeFiles/RegexEngine.dir/dfa.cc.s

CMakeFiles/RegexEngine.dir/dfa.cc.o.requires:

.PHONY : CMakeFiles/RegexEngine.dir/dfa.cc.o.requires

CMakeFiles/RegexEngine.dir/dfa.cc.o.provides: CMakeFiles/RegexEngine.dir/dfa.cc.o.requires
	$(MAKE) -f CMakeFiles/RegexEngine.dir/build.make CMakeFiles/RegexEngine.dir/dfa.cc.o.provides.build
.PHONY : CMakeFiles/RegexEngine.dir/dfa.cc.o.provides

CMakeFiles/RegexEngine.dir/dfa.cc.o.provides.build: CMakeFiles/RegexEngine.dir/dfa.cc.o


# Object files for target RegexEngine
RegexEngine_OBJECTS = \
"CMakeFiles/RegexEngine.dir/main.cc.o" \
"CMakeFiles/RegexEngine.dir/nfa.cc.o" \
"CMakeFiles/RegexEngine.dir/regex_parser.cc.o" \
"CMakeFiles/RegexEngine.dir/test.cc.o" \
"CMakeFiles/RegexEngine.dir/dfa.cc.o"

# External object files for target RegexEngine
RegexEngine_EXTERNAL_OBJECTS =

RegexEngine: CMakeFiles/RegexEngine.dir/main.cc.o
RegexEngine: CMakeFiles/RegexEngine.dir/nfa.cc.o
RegexEngine: CMakeFiles/RegexEngine.dir/regex_parser.cc.o
RegexEngine: CMakeFiles/RegexEngine.dir/test.cc.o
RegexEngine: CMakeFiles/RegexEngine.dir/dfa.cc.o
RegexEngine: CMakeFiles/RegexEngine.dir/build.make
RegexEngine: CMakeFiles/RegexEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable RegexEngine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RegexEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RegexEngine.dir/build: RegexEngine

.PHONY : CMakeFiles/RegexEngine.dir/build

CMakeFiles/RegexEngine.dir/requires: CMakeFiles/RegexEngine.dir/main.cc.o.requires
CMakeFiles/RegexEngine.dir/requires: CMakeFiles/RegexEngine.dir/nfa.cc.o.requires
CMakeFiles/RegexEngine.dir/requires: CMakeFiles/RegexEngine.dir/regex_parser.cc.o.requires
CMakeFiles/RegexEngine.dir/requires: CMakeFiles/RegexEngine.dir/test.cc.o.requires
CMakeFiles/RegexEngine.dir/requires: CMakeFiles/RegexEngine.dir/dfa.cc.o.requires

.PHONY : CMakeFiles/RegexEngine.dir/requires

CMakeFiles/RegexEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RegexEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RegexEngine.dir/clean

CMakeFiles/RegexEngine.dir/depend:
	cd /home/xvvx/code/RegexEngine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xvvx/code/RegexEngine /home/xvvx/code/RegexEngine /home/xvvx/code/RegexEngine/cmake-build-debug /home/xvvx/code/RegexEngine/cmake-build-debug /home/xvvx/code/RegexEngine/cmake-build-debug/CMakeFiles/RegexEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RegexEngine.dir/depend
