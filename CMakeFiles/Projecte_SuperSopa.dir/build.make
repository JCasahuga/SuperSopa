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
CMAKE_SOURCE_DIR = /home/miquel/Documents/Q5/A/Supersopa/SuperSopa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miquel/Documents/Q5/A/Supersopa/SuperSopa

# Include any dependencies generated for this target.
include CMakeFiles/Projecte_SuperSopa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Projecte_SuperSopa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projecte_SuperSopa.dir/flags.make

CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o: diccTrie.cc
CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccTrie.cc

CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccTrie.cc > CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.i

CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccTrie.cc -o CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.s

CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o: Trie.cc
CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/Trie.cc

CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/Trie.cc > CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.i

CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/Trie.cc -o CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.s

CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o: NodeTrie.cc
CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/NodeTrie.cc

CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/NodeTrie.cc > CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.i

CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/NodeTrie.cc -o CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.s

CMakeFiles/Projecte_SuperSopa.dir/program.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/program.cc.o: program.cc
CMakeFiles/Projecte_SuperSopa.dir/program.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/program.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/program.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/program.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/program.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/program.cc

CMakeFiles/Projecte_SuperSopa.dir/program.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/program.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/program.cc > CMakeFiles/Projecte_SuperSopa.dir/program.cc.i

CMakeFiles/Projecte_SuperSopa.dir/program.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/program.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/program.cc -o CMakeFiles/Projecte_SuperSopa.dir/program.cc.s

CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o: diccBloomFilter.cc
CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccBloomFilter.cc

CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccBloomFilter.cc > CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.i

CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccBloomFilter.cc -o CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.s

CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o: CMakeFiles/Projecte_SuperSopa.dir/flags.make
CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o: diccDHashing.cc
CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o: CMakeFiles/Projecte_SuperSopa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o -MF CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o.d -o CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o -c /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccDHashing.cc

CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccDHashing.cc > CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.i

CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/diccDHashing.cc -o CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.s

# Object files for target Projecte_SuperSopa
Projecte_SuperSopa_OBJECTS = \
"CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o" \
"CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o" \
"CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o" \
"CMakeFiles/Projecte_SuperSopa.dir/program.cc.o" \
"CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o" \
"CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o"

# External object files for target Projecte_SuperSopa
Projecte_SuperSopa_EXTERNAL_OBJECTS =

Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/diccTrie.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/Trie.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/NodeTrie.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/program.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/diccBloomFilter.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/diccDHashing.cc.o
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/build.make
Projecte_SuperSopa: CMakeFiles/Projecte_SuperSopa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Projecte_SuperSopa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Projecte_SuperSopa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projecte_SuperSopa.dir/build: Projecte_SuperSopa
.PHONY : CMakeFiles/Projecte_SuperSopa.dir/build

CMakeFiles/Projecte_SuperSopa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Projecte_SuperSopa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Projecte_SuperSopa.dir/clean

CMakeFiles/Projecte_SuperSopa.dir/depend:
	cd /home/miquel/Documents/Q5/A/Supersopa/SuperSopa && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miquel/Documents/Q5/A/Supersopa/SuperSopa /home/miquel/Documents/Q5/A/Supersopa/SuperSopa /home/miquel/Documents/Q5/A/Supersopa/SuperSopa /home/miquel/Documents/Q5/A/Supersopa/SuperSopa /home/miquel/Documents/Q5/A/Supersopa/SuperSopa/CMakeFiles/Projecte_SuperSopa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Projecte_SuperSopa.dir/depend

