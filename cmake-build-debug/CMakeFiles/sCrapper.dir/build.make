# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Rkhar\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.6817.32\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Rkhar\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\192.6817.32\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Rkhar\CLionProjects\sCrapper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sCrapper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sCrapper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sCrapper.dir/flags.make

CMakeFiles/sCrapper.dir/main.c.obj: CMakeFiles/sCrapper.dir/flags.make
CMakeFiles/sCrapper.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sCrapper.dir/main.c.obj"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\sCrapper.dir\main.c.obj   -c C:\Users\Rkhar\CLionProjects\sCrapper\main.c

CMakeFiles/sCrapper.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sCrapper.dir/main.c.i"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Rkhar\CLionProjects\sCrapper\main.c > CMakeFiles\sCrapper.dir\main.c.i

CMakeFiles/sCrapper.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sCrapper.dir/main.c.s"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Rkhar\CLionProjects\sCrapper\main.c -o CMakeFiles\sCrapper.dir\main.c.s

# Object files for target sCrapper
sCrapper_OBJECTS = \
"CMakeFiles/sCrapper.dir/main.c.obj"

# External object files for target sCrapper
sCrapper_EXTERNAL_OBJECTS =

sCrapper.exe: CMakeFiles/sCrapper.dir/main.c.obj
sCrapper.exe: CMakeFiles/sCrapper.dir/build.make
sCrapper.exe: CMakeFiles/sCrapper.dir/linklibs.rsp
sCrapper.exe: CMakeFiles/sCrapper.dir/objects1.rsp
sCrapper.exe: CMakeFiles/sCrapper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sCrapper.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sCrapper.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sCrapper.dir/build: sCrapper.exe

.PHONY : CMakeFiles/sCrapper.dir/build

CMakeFiles/sCrapper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\sCrapper.dir\cmake_clean.cmake
.PHONY : CMakeFiles/sCrapper.dir/clean

CMakeFiles/sCrapper.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Rkhar\CLionProjects\sCrapper C:\Users\Rkhar\CLionProjects\sCrapper C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug C:\Users\Rkhar\CLionProjects\sCrapper\cmake-build-debug\CMakeFiles\sCrapper.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sCrapper.dir/depend

