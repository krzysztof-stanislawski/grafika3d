# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = K:\studia\grafika3d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = K:\studia\grafika3d\cmake-build-debug-mingw

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include _deps/glfw-build/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/glfw-build/CMakeFiles/uninstall.dir/progress.make

_deps/glfw-build/CMakeFiles/uninstall:
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\_deps\glfw-build && "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -P K:/studia/grafika3d/cmake-build-debug-mingw/_deps/glfw-build/cmake_uninstall.cmake

uninstall: _deps/glfw-build/CMakeFiles/uninstall
uninstall: _deps/glfw-build/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
_deps/glfw-build/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : _deps/glfw-build/CMakeFiles/uninstall.dir/build

_deps/glfw-build/CMakeFiles/uninstall.dir/clean:
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\_deps\glfw-build && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : _deps/glfw-build/CMakeFiles/uninstall.dir/clean

_deps/glfw-build/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" K:\studia\grafika3d K:\studia\grafika3d\cmake-build-debug-mingw\_deps\glfw-src K:\studia\grafika3d\cmake-build-debug-mingw K:\studia\grafika3d\cmake-build-debug-mingw\_deps\glfw-build K:\studia\grafika3d\cmake-build-debug-mingw\_deps\glfw-build\CMakeFiles\uninstall.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/glfw-build/CMakeFiles/uninstall.dir/depend

