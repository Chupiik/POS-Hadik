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
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.c.o: /home/chupac10/POS-Hadik/main.c
CMakeFiles/main.dir/main.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/main.c.o -MF CMakeFiles/main.dir/main.c.o.d -o CMakeFiles/main.dir/main.c.o -c /home/chupac10/POS-Hadik/main.c

CMakeFiles/main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/main.c > CMakeFiles/main.dir/main.c.i

CMakeFiles/main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/main.c -o CMakeFiles/main.dir/main.c.s

CMakeFiles/main.dir/server.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/server.c.o: /home/chupac10/POS-Hadik/server.c
CMakeFiles/main.dir/server.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/server.c.o -MF CMakeFiles/main.dir/server.c.o.d -o CMakeFiles/main.dir/server.c.o -c /home/chupac10/POS-Hadik/server.c

CMakeFiles/main.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/server.c > CMakeFiles/main.dir/server.c.i

CMakeFiles/main.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/server.c -o CMakeFiles/main.dir/server.c.s

CMakeFiles/main.dir/plocha.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/plocha.c.o: /home/chupac10/POS-Hadik/plocha.c
CMakeFiles/main.dir/plocha.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/plocha.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/plocha.c.o -MF CMakeFiles/main.dir/plocha.c.o.d -o CMakeFiles/main.dir/plocha.c.o -c /home/chupac10/POS-Hadik/plocha.c

CMakeFiles/main.dir/plocha.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/plocha.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/plocha.c > CMakeFiles/main.dir/plocha.c.i

CMakeFiles/main.dir/plocha.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/plocha.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/plocha.c -o CMakeFiles/main.dir/plocha.c.s

CMakeFiles/main.dir/hra.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/hra.c.o: /home/chupac10/POS-Hadik/hra.c
CMakeFiles/main.dir/hra.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/hra.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/hra.c.o -MF CMakeFiles/main.dir/hra.c.o.d -o CMakeFiles/main.dir/hra.c.o -c /home/chupac10/POS-Hadik/hra.c

CMakeFiles/main.dir/hra.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/hra.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/hra.c > CMakeFiles/main.dir/hra.c.i

CMakeFiles/main.dir/hra.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/hra.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/hra.c -o CMakeFiles/main.dir/hra.c.s

CMakeFiles/main.dir/snake.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/snake.c.o: /home/chupac10/POS-Hadik/snake.c
CMakeFiles/main.dir/snake.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/snake.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/snake.c.o -MF CMakeFiles/main.dir/snake.c.o.d -o CMakeFiles/main.dir/snake.c.o -c /home/chupac10/POS-Hadik/snake.c

CMakeFiles/main.dir/snake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/snake.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/snake.c > CMakeFiles/main.dir/snake.c.i

CMakeFiles/main.dir/snake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/snake.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/snake.c -o CMakeFiles/main.dir/snake.c.s

CMakeFiles/main.dir/input.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/input.c.o: /home/chupac10/POS-Hadik/input.c
CMakeFiles/main.dir/input.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/input.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/input.c.o -MF CMakeFiles/main.dir/input.c.o.d -o CMakeFiles/main.dir/input.c.o -c /home/chupac10/POS-Hadik/input.c

CMakeFiles/main.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/input.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/input.c > CMakeFiles/main.dir/input.c.i

CMakeFiles/main.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/input.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/input.c -o CMakeFiles/main.dir/input.c.s

CMakeFiles/main.dir/client.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/client.c.o: /home/chupac10/POS-Hadik/client.c
CMakeFiles/main.dir/client.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/main.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/client.c.o -MF CMakeFiles/main.dir/client.c.o.d -o CMakeFiles/main.dir/client.c.o -c /home/chupac10/POS-Hadik/client.c

CMakeFiles/main.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chupac10/POS-Hadik/client.c > CMakeFiles/main.dir/client.c.i

CMakeFiles/main.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chupac10/POS-Hadik/client.c -o CMakeFiles/main.dir/client.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.c.o" \
"CMakeFiles/main.dir/server.c.o" \
"CMakeFiles/main.dir/plocha.c.o" \
"CMakeFiles/main.dir/hra.c.o" \
"CMakeFiles/main.dir/snake.c.o" \
"CMakeFiles/main.dir/input.c.o" \
"CMakeFiles/main.dir/client.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.c.o
main: CMakeFiles/main.dir/server.c.o
main: CMakeFiles/main.dir/plocha.c.o
main: CMakeFiles/main.dir/hra.c.o
main: CMakeFiles/main.dir/snake.c.o
main: CMakeFiles/main.dir/input.c.o
main: CMakeFiles/main.dir/client.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chupac10/POS-Hadik/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/chupac10/POS-Hadik/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chupac10/POS-Hadik /home/chupac10/POS-Hadik /home/chupac10/POS-Hadik/build /home/chupac10/POS-Hadik/build /home/chupac10/POS-Hadik/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

