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
CMAKE_SOURCE_DIR = /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build

# Utility rule file for NightlySubmit.

# Include the progress variables for this target.
include test/CMakeFiles/NightlySubmit.dir/progress.make

test/CMakeFiles/NightlySubmit:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build/test && /usr/bin/ctest -D NightlySubmit

NightlySubmit: test/CMakeFiles/NightlySubmit
NightlySubmit: test/CMakeFiles/NightlySubmit.dir/build.make

.PHONY : NightlySubmit

# Rule to build all files generated by this target.
test/CMakeFiles/NightlySubmit.dir/build: NightlySubmit

.PHONY : test/CMakeFiles/NightlySubmit.dir/build

test/CMakeFiles/NightlySubmit.dir/clean:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build/test && $(CMAKE_COMMAND) -P CMakeFiles/NightlySubmit.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/NightlySubmit.dir/clean

test/CMakeFiles/NightlySubmit.dir/depend:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0 /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build/test /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/build/test/CMakeFiles/NightlySubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/NightlySubmit.dir/depend

