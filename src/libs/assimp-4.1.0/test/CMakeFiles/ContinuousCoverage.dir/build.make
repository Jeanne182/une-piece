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
CMAKE_BINARY_DIR = /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0

# Utility rule file for ContinuousCoverage.

# Include the progress variables for this target.
include test/CMakeFiles/ContinuousCoverage.dir/progress.make

test/CMakeFiles/ContinuousCoverage:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test && /usr/bin/ctest -D ContinuousCoverage

ContinuousCoverage: test/CMakeFiles/ContinuousCoverage
ContinuousCoverage: test/CMakeFiles/ContinuousCoverage.dir/build.make

.PHONY : ContinuousCoverage

# Rule to build all files generated by this target.
test/CMakeFiles/ContinuousCoverage.dir/build: ContinuousCoverage

.PHONY : test/CMakeFiles/ContinuousCoverage.dir/build

test/CMakeFiles/ContinuousCoverage.dir/clean:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousCoverage.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/ContinuousCoverage.dir/clean

test/CMakeFiles/ContinuousCoverage.dir/depend:
	cd /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0 /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0 /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test /home/mmmaxou/Imac/une-piece/libs/assimp-4.1.0/test/CMakeFiles/ContinuousCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/ContinuousCoverage.dir/depend

