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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\esteb\Desktop\bdii-lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fileOrganization.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fileOrganization.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fileOrganization.dir/flags.make

CMakeFiles/fileOrganization.dir/p4.cpp.obj: CMakeFiles/fileOrganization.dir/flags.make
CMakeFiles/fileOrganization.dir/p4.cpp.obj: ../p4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fileOrganization.dir/p4.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\fileOrganization.dir\p4.cpp.obj -c C:\Users\esteb\Desktop\bdii-lab1\p4.cpp

CMakeFiles/fileOrganization.dir/p4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fileOrganization.dir/p4.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\esteb\Desktop\bdii-lab1\p4.cpp > CMakeFiles\fileOrganization.dir\p4.cpp.i

CMakeFiles/fileOrganization.dir/p4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fileOrganization.dir/p4.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\esteb\Desktop\bdii-lab1\p4.cpp -o CMakeFiles\fileOrganization.dir\p4.cpp.s

# Object files for target fileOrganization
fileOrganization_OBJECTS = \
"CMakeFiles/fileOrganization.dir/p4.cpp.obj"

# External object files for target fileOrganization
fileOrganization_EXTERNAL_OBJECTS =

fileOrganization.exe: CMakeFiles/fileOrganization.dir/p4.cpp.obj
fileOrganization.exe: CMakeFiles/fileOrganization.dir/build.make
fileOrganization.exe: CMakeFiles/fileOrganization.dir/linklibs.rsp
fileOrganization.exe: CMakeFiles/fileOrganization.dir/objects1.rsp
fileOrganization.exe: CMakeFiles/fileOrganization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fileOrganization.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\fileOrganization.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fileOrganization.dir/build: fileOrganization.exe

.PHONY : CMakeFiles/fileOrganization.dir/build

CMakeFiles/fileOrganization.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\fileOrganization.dir\cmake_clean.cmake
.PHONY : CMakeFiles/fileOrganization.dir/clean

CMakeFiles/fileOrganization.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\esteb\Desktop\bdii-lab1 C:\Users\esteb\Desktop\bdii-lab1 C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug C:\Users\esteb\Desktop\bdii-lab1\cmake-build-debug\CMakeFiles\fileOrganization.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fileOrganization.dir/depend

