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
CMAKE_SOURCE_DIR = /home/danilo/projects/mc504/projeto1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/danilo/projects/mc504/projeto1

# Include any dependencies generated for this target.
include CMakeFiles/projeto1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/projeto1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projeto1.dir/flags.make

CMakeFiles/projeto1.dir/main.c.o: CMakeFiles/projeto1.dir/flags.make
CMakeFiles/projeto1.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/danilo/projects/mc504/projeto1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/projeto1.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/projeto1.dir/main.c.o   -c /home/danilo/projects/mc504/projeto1/main.c

CMakeFiles/projeto1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projeto1.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/danilo/projects/mc504/projeto1/main.c > CMakeFiles/projeto1.dir/main.c.i

CMakeFiles/projeto1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projeto1.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/danilo/projects/mc504/projeto1/main.c -o CMakeFiles/projeto1.dir/main.c.s

CMakeFiles/projeto1.dir/main.c.o.requires:

.PHONY : CMakeFiles/projeto1.dir/main.c.o.requires

CMakeFiles/projeto1.dir/main.c.o.provides: CMakeFiles/projeto1.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/projeto1.dir/build.make CMakeFiles/projeto1.dir/main.c.o.provides.build
.PHONY : CMakeFiles/projeto1.dir/main.c.o.provides

CMakeFiles/projeto1.dir/main.c.o.provides.build: CMakeFiles/projeto1.dir/main.c.o


# Object files for target projeto1
projeto1_OBJECTS = \
"CMakeFiles/projeto1.dir/main.c.o"

# External object files for target projeto1
projeto1_EXTERNAL_OBJECTS =

projeto1: CMakeFiles/projeto1.dir/main.c.o
projeto1: CMakeFiles/projeto1.dir/build.make
projeto1: CMakeFiles/projeto1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/danilo/projects/mc504/projeto1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable projeto1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/projeto1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projeto1.dir/build: projeto1

.PHONY : CMakeFiles/projeto1.dir/build

CMakeFiles/projeto1.dir/requires: CMakeFiles/projeto1.dir/main.c.o.requires

.PHONY : CMakeFiles/projeto1.dir/requires

CMakeFiles/projeto1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/projeto1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/projeto1.dir/clean

CMakeFiles/projeto1.dir/depend:
	cd /home/danilo/projects/mc504/projeto1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/danilo/projects/mc504/projeto1 /home/danilo/projects/mc504/projeto1 /home/danilo/projects/mc504/projeto1 /home/danilo/projects/mc504/projeto1 /home/danilo/projects/mc504/projeto1/CMakeFiles/projeto1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projeto1.dir/depend

