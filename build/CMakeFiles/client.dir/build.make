# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/chupac10/POS-Hadik

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chupac10/POS-Hadik/build

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/main_client.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/main_client.c.o: /home/chupac10/POS-Hadik/main_client.c
CMakeFiles/client.dir/main_client.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client.dir/main_client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/main_client.c.o -MF CMakeFiles/client.dir/main_client.c.o.d -o CMakeFiles/client.dir/main_client.c.o -c /home/chupac10/POS-Hadik/main_client.c

CMakeFiles/client.dir/main_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/main_client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/main_client.c > CMakeFiles/client.dir/main_client.c.i

CMakeFiles/client.dir/main_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/main_client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/main_client.c -o CMakeFiles/client.dir/main_client.c.s

CMakeFiles/client.dir/client.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client.c.o: /home/chupac10/POS-Hadik/client.c
CMakeFiles/client.dir/client.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/client.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/client.c.o -MF CMakeFiles/client.dir/client.c.o.d -o CMakeFiles/client.dir/client.c.o -c /home/chupac10/POS-Hadik/client.c

CMakeFiles/client.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/client.c > CMakeFiles/client.dir/client.c.i

CMakeFiles/client.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/client.c -o CMakeFiles/client.dir/client.c.s

CMakeFiles/client.dir/plocha.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/plocha.c.o: /home/chupac10/POS-Hadik/plocha.c
CMakeFiles/client.dir/plocha.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/client.dir/plocha.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/plocha.c.o -MF CMakeFiles/client.dir/plocha.c.o.d -o CMakeFiles/client.dir/plocha.c.o -c /home/chupac10/POS-Hadik/plocha.c

CMakeFiles/client.dir/plocha.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/plocha.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/plocha.c > CMakeFiles/client.dir/plocha.c.i

CMakeFiles/client.dir/plocha.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/plocha.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/plocha.c -o CMakeFiles/client.dir/plocha.c.s

CMakeFiles/client.dir/hra.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/hra.c.o: /home/chupac10/POS-Hadik/hra.c
CMakeFiles/client.dir/hra.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/client.dir/hra.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/hra.c.o -MF CMakeFiles/client.dir/hra.c.o.d -o CMakeFiles/client.dir/hra.c.o -c /home/chupac10/POS-Hadik/hra.c

CMakeFiles/client.dir/hra.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/hra.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/hra.c > CMakeFiles/client.dir/hra.c.i

CMakeFiles/client.dir/hra.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/hra.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/hra.c -o CMakeFiles/client.dir/hra.c.s

CMakeFiles/client.dir/snake.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/snake.c.o: /home/chupac10/POS-Hadik/snake.c
CMakeFiles/client.dir/snake.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/client.dir/snake.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/snake.c.o -MF CMakeFiles/client.dir/snake.c.o.d -o CMakeFiles/client.dir/snake.c.o -c /home/chupac10/POS-Hadik/snake.c

CMakeFiles/client.dir/snake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/snake.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/snake.c > CMakeFiles/client.dir/snake.c.i

CMakeFiles/client.dir/snake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/snake.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/snake.c -o CMakeFiles/client.dir/snake.c.s

CMakeFiles/client.dir/input.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/input.c.o: /home/chupac10/POS-Hadik/input.c
CMakeFiles/client.dir/input.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/client.dir/input.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/input.c.o -MF CMakeFiles/client.dir/input.c.o.d -o CMakeFiles/client.dir/input.c.o -c /home/chupac10/POS-Hadik/input.c

CMakeFiles/client.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/input.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/input.c > CMakeFiles/client.dir/input.c.i

CMakeFiles/client.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/input.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/input.c -o CMakeFiles/client.dir/input.c.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/main_client.c.o" \
"CMakeFiles/client.dir/client.c.o" \
"CMakeFiles/client.dir/plocha.c.o" \
"CMakeFiles/client.dir/hra.c.o" \
"CMakeFiles/client.dir/snake.c.o" \
"CMakeFiles/client.dir/input.c.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/main_client.c.o
client: CMakeFiles/client.dir/client.c.o
client: CMakeFiles/client.dir/plocha.c.o
client: CMakeFiles/client.dir/hra.c.o
client: CMakeFiles/client.dir/snake.c.o
client: CMakeFiles/client.dir/input.c.o
client: CMakeFiles/client.dir/build.make
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/chupac10/POS-Hadik/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chupac10/POS-Hadik /home/chupac10/POS-Hadik /home/chupac10/POS-Hadik/build /home/chupac10/POS-Hadik/build /home/chupac10/POS-Hadik/build/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

