# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build"

# Include any dependencies generated for this target.
include CMakeFiles/anaylysis.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/anaylysis.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/anaylysis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anaylysis.dir/flags.make

CMakeFiles/anaylysis.dir/src/analysis.c.obj: CMakeFiles/anaylysis.dir/flags.make
CMakeFiles/anaylysis.dir/src/analysis.c.obj: CMakeFiles/anaylysis.dir/includes_C.rsp
CMakeFiles/anaylysis.dir/src/analysis.c.obj: C:/Users/User/Documents/Year\ 4/OS/hw2/CIS520_HW2/hw2/hw2/src/analysis.c
CMakeFiles/anaylysis.dir/src/analysis.c.obj: CMakeFiles/anaylysis.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/anaylysis.dir/src/analysis.c.obj"
	C:/Users/User/Documents/compilers/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/anaylysis.dir/src/analysis.c.obj -MF CMakeFiles/anaylysis.dir/src/analysis.c.obj.d -o CMakeFiles/anaylysis.dir/src/analysis.c.obj -c "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/src/analysis.c"

CMakeFiles/anaylysis.dir/src/analysis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/anaylysis.dir/src/analysis.c.i"
	C:/Users/User/Documents/compilers/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/src/analysis.c" > CMakeFiles/anaylysis.dir/src/analysis.c.i

CMakeFiles/anaylysis.dir/src/analysis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/anaylysis.dir/src/analysis.c.s"
	C:/Users/User/Documents/compilers/w64devkit/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/src/analysis.c" -o CMakeFiles/anaylysis.dir/src/analysis.c.s

# Object files for target anaylysis
anaylysis_OBJECTS = \
"CMakeFiles/anaylysis.dir/src/analysis.c.obj"

# External object files for target anaylysis
anaylysis_EXTERNAL_OBJECTS =

anaylysis.exe: CMakeFiles/anaylysis.dir/src/analysis.c.obj
anaylysis.exe: CMakeFiles/anaylysis.dir/build.make
anaylysis.exe: CMakeFiles/anaylysis.dir/linkLibs.rsp
anaylysis.exe: CMakeFiles/anaylysis.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable anaylysis.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/anaylysis.dir/objects.a
	C:/Users/User/Documents/compilers/w64devkit/bin/ar.exe qc CMakeFiles/anaylysis.dir/objects.a @CMakeFiles/anaylysis.dir/objects1.rsp
	C:/Users/User/Documents/compilers/w64devkit/bin/gcc.exe -std=c11 -Wall -Wextra -Wshadow -Werror -g -Wl,--whole-archive CMakeFiles/anaylysis.dir/objects.a -Wl,--no-whole-archive -o anaylysis.exe -Wl,--out-implib,libanaylysis.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/anaylysis.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/anaylysis.dir/build: anaylysis.exe
.PHONY : CMakeFiles/anaylysis.dir/build

CMakeFiles/anaylysis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anaylysis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anaylysis.dir/clean

CMakeFiles/anaylysis.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2" "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2" "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build" "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build" "C:/Users/User/Documents/Year 4/OS/hw2/CIS520_HW2/hw2/hw2/build/CMakeFiles/anaylysis.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/anaylysis.dir/depend
