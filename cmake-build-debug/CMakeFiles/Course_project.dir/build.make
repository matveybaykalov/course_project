# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bayk/AL_labs/course_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bayk/AL_labs/course_project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Course_project.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Course_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Course_project.dir/flags.make

CMakeFiles/Course_project.dir/main.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Course_project.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/main.cpp.o -c /home/bayk/AL_labs/course_project/main.cpp

CMakeFiles/Course_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bayk/AL_labs/course_project/main.cpp > CMakeFiles/Course_project.dir/main.cpp.i

CMakeFiles/Course_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bayk/AL_labs/course_project/main.cpp -o CMakeFiles/Course_project.dir/main.cpp.s

CMakeFiles/Course_project.dir/Mytemplate.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/Mytemplate.cpp.o: ../Mytemplate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Course_project.dir/Mytemplate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/Mytemplate.cpp.o -c /home/bayk/AL_labs/course_project/Mytemplate.cpp

CMakeFiles/Course_project.dir/Mytemplate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/Mytemplate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bayk/AL_labs/course_project/Mytemplate.cpp > CMakeFiles/Course_project.dir/Mytemplate.cpp.i

CMakeFiles/Course_project.dir/Mytemplate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/Mytemplate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bayk/AL_labs/course_project/Mytemplate.cpp -o CMakeFiles/Course_project.dir/Mytemplate.cpp.s

CMakeFiles/Course_project.dir/Keccak.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/Keccak.cpp.o: ../Keccak.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Course_project.dir/Keccak.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/Keccak.cpp.o -c /home/bayk/AL_labs/course_project/Keccak.cpp

CMakeFiles/Course_project.dir/Keccak.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/Keccak.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bayk/AL_labs/course_project/Keccak.cpp > CMakeFiles/Course_project.dir/Keccak.cpp.i

CMakeFiles/Course_project.dir/Keccak.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/Keccak.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bayk/AL_labs/course_project/Keccak.cpp -o CMakeFiles/Course_project.dir/Keccak.cpp.s

CMakeFiles/Course_project.dir/RSA.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/RSA.cpp.o: ../RSA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Course_project.dir/RSA.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/RSA.cpp.o -c /home/bayk/AL_labs/course_project/RSA.cpp

CMakeFiles/Course_project.dir/RSA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/RSA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bayk/AL_labs/course_project/RSA.cpp > CMakeFiles/Course_project.dir/RSA.cpp.i

CMakeFiles/Course_project.dir/RSA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/RSA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bayk/AL_labs/course_project/RSA.cpp -o CMakeFiles/Course_project.dir/RSA.cpp.s

CMakeFiles/Course_project.dir/Bit_number.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/Bit_number.cpp.o: ../Bit_number.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Course_project.dir/Bit_number.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/Bit_number.cpp.o -c /home/bayk/AL_labs/course_project/Bit_number.cpp

CMakeFiles/Course_project.dir/Bit_number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/Bit_number.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bayk/AL_labs/course_project/Bit_number.cpp > CMakeFiles/Course_project.dir/Bit_number.cpp.i

CMakeFiles/Course_project.dir/Bit_number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/Bit_number.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bayk/AL_labs/course_project/Bit_number.cpp -o CMakeFiles/Course_project.dir/Bit_number.cpp.s

# Object files for target Course_project
Course_project_OBJECTS = \
"CMakeFiles/Course_project.dir/main.cpp.o" \
"CMakeFiles/Course_project.dir/Mytemplate.cpp.o" \
"CMakeFiles/Course_project.dir/Keccak.cpp.o" \
"CMakeFiles/Course_project.dir/RSA.cpp.o" \
"CMakeFiles/Course_project.dir/Bit_number.cpp.o"

# External object files for target Course_project
Course_project_EXTERNAL_OBJECTS =

Course_project: CMakeFiles/Course_project.dir/main.cpp.o
Course_project: CMakeFiles/Course_project.dir/Mytemplate.cpp.o
Course_project: CMakeFiles/Course_project.dir/Keccak.cpp.o
Course_project: CMakeFiles/Course_project.dir/RSA.cpp.o
Course_project: CMakeFiles/Course_project.dir/Bit_number.cpp.o
Course_project: CMakeFiles/Course_project.dir/build.make
Course_project: CMakeFiles/Course_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Course_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Course_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Course_project.dir/build: Course_project
.PHONY : CMakeFiles/Course_project.dir/build

CMakeFiles/Course_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Course_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Course_project.dir/clean

CMakeFiles/Course_project.dir/depend:
	cd /home/bayk/AL_labs/course_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bayk/AL_labs/course_project /home/bayk/AL_labs/course_project /home/bayk/AL_labs/course_project/cmake-build-debug /home/bayk/AL_labs/course_project/cmake-build-debug /home/bayk/AL_labs/course_project/cmake-build-debug/CMakeFiles/Course_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Course_project.dir/depend

