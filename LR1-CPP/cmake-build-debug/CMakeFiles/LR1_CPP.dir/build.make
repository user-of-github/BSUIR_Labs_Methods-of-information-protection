# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/LR1_CPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LR1_CPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR1_CPP.dir/flags.make

CMakeFiles/LR1_CPP.dir/main.cpp.obj: CMakeFiles/LR1_CPP.dir/flags.make
CMakeFiles/LR1_CPP.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LR1_CPP.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\LR1_CPP.dir\main.cpp.obj -c "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\main.cpp"

CMakeFiles/LR1_CPP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LR1_CPP.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\main.cpp" > CMakeFiles\LR1_CPP.dir\main.cpp.i

CMakeFiles/LR1_CPP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LR1_CPP.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\main.cpp" -o CMakeFiles\LR1_CPP.dir\main.cpp.s

# Object files for target LR1_CPP
LR1_CPP_OBJECTS = \
"CMakeFiles/LR1_CPP.dir/main.cpp.obj"

# External object files for target LR1_CPP
LR1_CPP_EXTERNAL_OBJECTS =

LR1_CPP.exe: CMakeFiles/LR1_CPP.dir/main.cpp.obj
LR1_CPP.exe: CMakeFiles/LR1_CPP.dir/build.make
LR1_CPP.exe: CMakeFiles/LR1_CPP.dir/linklibs.rsp
LR1_CPP.exe: CMakeFiles/LR1_CPP.dir/objects1.rsp
LR1_CPP.exe: CMakeFiles/LR1_CPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LR1_CPP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR1_CPP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR1_CPP.dir/build: LR1_CPP.exe

.PHONY : CMakeFiles/LR1_CPP.dir/build

CMakeFiles/LR1_CPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR1_CPP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR1_CPP.dir/clean

CMakeFiles/LR1_CPP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP" "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP" "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug" "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug" "D:\Other\HomeWork\Methods Of Information Protection\LR1-CPP\cmake-build-debug\CMakeFiles\LR1_CPP.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LR1_CPP.dir/depend

