# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PRG2_labo2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PRG2_labo2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PRG2_labo2.dir/flags.make

CMakeFiles/PRG2_labo2.dir/main.c.obj: CMakeFiles/PRG2_labo2.dir/flags.make
CMakeFiles/PRG2_labo2.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PRG2_labo2.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\PRG2_labo2.dir\main.c.obj   -c D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\main.c

CMakeFiles/PRG2_labo2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PRG2_labo2.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\main.c > CMakeFiles\PRG2_labo2.dir\main.c.i

CMakeFiles/PRG2_labo2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PRG2_labo2.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\main.c -o CMakeFiles\PRG2_labo2.dir\main.c.s

# Object files for target PRG2_labo2
PRG2_labo2_OBJECTS = \
"CMakeFiles/PRG2_labo2.dir/main.c.obj"

# External object files for target PRG2_labo2
PRG2_labo2_EXTERNAL_OBJECTS =

PRG2_labo2.exe: CMakeFiles/PRG2_labo2.dir/main.c.obj
PRG2_labo2.exe: CMakeFiles/PRG2_labo2.dir/build.make
PRG2_labo2.exe: CMakeFiles/PRG2_labo2.dir/linklibs.rsp
PRG2_labo2.exe: CMakeFiles/PRG2_labo2.dir/objects1.rsp
PRG2_labo2.exe: CMakeFiles/PRG2_labo2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable PRG2_labo2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PRG2_labo2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PRG2_labo2.dir/build: PRG2_labo2.exe

.PHONY : CMakeFiles/PRG2_labo2.dir/build

CMakeFiles/PRG2_labo2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PRG2_labo2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PRG2_labo2.dir/clean

CMakeFiles/PRG2_labo2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2 D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2 D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug D:\HEIG-VD\Semestre_2\PRG2\Labo\Labo2\PRG2-labo2\cmake-build-debug\CMakeFiles\PRG2_labo2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PRG2_labo2.dir/depend
