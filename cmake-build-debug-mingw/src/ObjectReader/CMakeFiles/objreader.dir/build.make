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

# Include any dependencies generated for this target.
include src/ObjectReader/CMakeFiles/objreader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/ObjectReader/CMakeFiles/objreader.dir/compiler_depend.make

# Include the progress variables for this target.
include src/ObjectReader/CMakeFiles/objreader.dir/progress.make

# Include the compile flags for this target's objects.
include src/ObjectReader/CMakeFiles/objreader.dir/flags.make

src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj: src/ObjectReader/CMakeFiles/objreader.dir/flags.make
src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj: src/ObjectReader/CMakeFiles/objreader.dir/includes_CXX.rsp
src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj: K:/studia/grafika3d/src/ObjectReader/obj_reader.cpp
src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj: src/ObjectReader/CMakeFiles/objreader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=K:\studia\grafika3d\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj"
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj -MF CMakeFiles\objreader.dir\obj_reader.cpp.obj.d -o CMakeFiles\objreader.dir\obj_reader.cpp.obj -c K:\studia\grafika3d\src\ObjectReader\obj_reader.cpp

src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/objreader.dir/obj_reader.cpp.i"
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E K:\studia\grafika3d\src\ObjectReader\obj_reader.cpp > CMakeFiles\objreader.dir\obj_reader.cpp.i

src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/objreader.dir/obj_reader.cpp.s"
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S K:\studia\grafika3d\src\ObjectReader\obj_reader.cpp -o CMakeFiles\objreader.dir\obj_reader.cpp.s

# Object files for target objreader
objreader_OBJECTS = \
"CMakeFiles/objreader.dir/obj_reader.cpp.obj"

# External object files for target objreader
objreader_EXTERNAL_OBJECTS = \
"K:/studia/grafika3d/cmake-build-debug-mingw/CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_6/glad/src/gl.c.obj"

src/ObjectReader/libobjreader.a: src/ObjectReader/CMakeFiles/objreader.dir/obj_reader.cpp.obj
src/ObjectReader/libobjreader.a: CMakeFiles/glad.dir/src/3rdParty/glad/glad_4_6/glad/src/gl.c.obj
src/ObjectReader/libobjreader.a: src/ObjectReader/CMakeFiles/objreader.dir/build.make
src/ObjectReader/libobjreader.a: src/ObjectReader/CMakeFiles/objreader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=K:\studia\grafika3d\cmake-build-debug-mingw\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libobjreader.a"
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && $(CMAKE_COMMAND) -P CMakeFiles\objreader.dir\cmake_clean_target.cmake
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\objreader.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ObjectReader/CMakeFiles/objreader.dir/build: src/ObjectReader/libobjreader.a
.PHONY : src/ObjectReader/CMakeFiles/objreader.dir/build

src/ObjectReader/CMakeFiles/objreader.dir/clean:
	cd /d K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader && $(CMAKE_COMMAND) -P CMakeFiles\objreader.dir\cmake_clean.cmake
.PHONY : src/ObjectReader/CMakeFiles/objreader.dir/clean

src/ObjectReader/CMakeFiles/objreader.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" K:\studia\grafika3d K:\studia\grafika3d\src\ObjectReader K:\studia\grafika3d\cmake-build-debug-mingw K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader K:\studia\grafika3d\cmake-build-debug-mingw\src\ObjectReader\CMakeFiles\objreader.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/ObjectReader/CMakeFiles/objreader.dir/depend

