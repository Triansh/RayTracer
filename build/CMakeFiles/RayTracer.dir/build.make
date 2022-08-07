# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/trios/Desktop/SEM7/VR/RayTracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/trios/Desktop/SEM7/VR/RayTracer/build

# Include any dependencies generated for this target.
include CMakeFiles/RayTracer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RayTracer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracer.dir/flags.make

CMakeFiles/RayTracer.dir/src/camera.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/camera.cpp.o: ../src/camera.cpp
CMakeFiles/RayTracer.dir/src/camera.cpp.o: CMakeFiles/RayTracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RayTracer.dir/src/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracer.dir/src/camera.cpp.o -MF CMakeFiles/RayTracer.dir/src/camera.cpp.o.d -o CMakeFiles/RayTracer.dir/src/camera.cpp.o -c /home/trios/Desktop/SEM7/VR/RayTracer/src/camera.cpp

CMakeFiles/RayTracer.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/trios/Desktop/SEM7/VR/RayTracer/src/camera.cpp > CMakeFiles/RayTracer.dir/src/camera.cpp.i

CMakeFiles/RayTracer.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/trios/Desktop/SEM7/VR/RayTracer/src/camera.cpp -o CMakeFiles/RayTracer.dir/src/camera.cpp.s

CMakeFiles/RayTracer.dir/src/hittable.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/hittable.cpp.o: ../src/hittable.cpp
CMakeFiles/RayTracer.dir/src/hittable.cpp.o: CMakeFiles/RayTracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RayTracer.dir/src/hittable.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracer.dir/src/hittable.cpp.o -MF CMakeFiles/RayTracer.dir/src/hittable.cpp.o.d -o CMakeFiles/RayTracer.dir/src/hittable.cpp.o -c /home/trios/Desktop/SEM7/VR/RayTracer/src/hittable.cpp

CMakeFiles/RayTracer.dir/src/hittable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/hittable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/trios/Desktop/SEM7/VR/RayTracer/src/hittable.cpp > CMakeFiles/RayTracer.dir/src/hittable.cpp.i

CMakeFiles/RayTracer.dir/src/hittable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/hittable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/trios/Desktop/SEM7/VR/RayTracer/src/hittable.cpp -o CMakeFiles/RayTracer.dir/src/hittable.cpp.s

CMakeFiles/RayTracer.dir/src/main.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/RayTracer.dir/src/main.cpp.o: CMakeFiles/RayTracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RayTracer.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracer.dir/src/main.cpp.o -MF CMakeFiles/RayTracer.dir/src/main.cpp.o.d -o CMakeFiles/RayTracer.dir/src/main.cpp.o -c /home/trios/Desktop/SEM7/VR/RayTracer/src/main.cpp

CMakeFiles/RayTracer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/trios/Desktop/SEM7/VR/RayTracer/src/main.cpp > CMakeFiles/RayTracer.dir/src/main.cpp.i

CMakeFiles/RayTracer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/trios/Desktop/SEM7/VR/RayTracer/src/main.cpp -o CMakeFiles/RayTracer.dir/src/main.cpp.s

CMakeFiles/RayTracer.dir/src/metal.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/metal.cpp.o: ../src/metal.cpp
CMakeFiles/RayTracer.dir/src/metal.cpp.o: CMakeFiles/RayTracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RayTracer.dir/src/metal.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracer.dir/src/metal.cpp.o -MF CMakeFiles/RayTracer.dir/src/metal.cpp.o.d -o CMakeFiles/RayTracer.dir/src/metal.cpp.o -c /home/trios/Desktop/SEM7/VR/RayTracer/src/metal.cpp

CMakeFiles/RayTracer.dir/src/metal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/metal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/trios/Desktop/SEM7/VR/RayTracer/src/metal.cpp > CMakeFiles/RayTracer.dir/src/metal.cpp.i

CMakeFiles/RayTracer.dir/src/metal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/metal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/trios/Desktop/SEM7/VR/RayTracer/src/metal.cpp -o CMakeFiles/RayTracer.dir/src/metal.cpp.s

CMakeFiles/RayTracer.dir/src/sphere.cpp.o: CMakeFiles/RayTracer.dir/flags.make
CMakeFiles/RayTracer.dir/src/sphere.cpp.o: ../src/sphere.cpp
CMakeFiles/RayTracer.dir/src/sphere.cpp.o: CMakeFiles/RayTracer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RayTracer.dir/src/sphere.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracer.dir/src/sphere.cpp.o -MF CMakeFiles/RayTracer.dir/src/sphere.cpp.o.d -o CMakeFiles/RayTracer.dir/src/sphere.cpp.o -c /home/trios/Desktop/SEM7/VR/RayTracer/src/sphere.cpp

CMakeFiles/RayTracer.dir/src/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracer.dir/src/sphere.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/trios/Desktop/SEM7/VR/RayTracer/src/sphere.cpp > CMakeFiles/RayTracer.dir/src/sphere.cpp.i

CMakeFiles/RayTracer.dir/src/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracer.dir/src/sphere.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/trios/Desktop/SEM7/VR/RayTracer/src/sphere.cpp -o CMakeFiles/RayTracer.dir/src/sphere.cpp.s

# Object files for target RayTracer
RayTracer_OBJECTS = \
"CMakeFiles/RayTracer.dir/src/camera.cpp.o" \
"CMakeFiles/RayTracer.dir/src/hittable.cpp.o" \
"CMakeFiles/RayTracer.dir/src/main.cpp.o" \
"CMakeFiles/RayTracer.dir/src/metal.cpp.o" \
"CMakeFiles/RayTracer.dir/src/sphere.cpp.o"

# External object files for target RayTracer
RayTracer_EXTERNAL_OBJECTS =

RayTracer: CMakeFiles/RayTracer.dir/src/camera.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/hittable.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/main.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/metal.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/src/sphere.cpp.o
RayTracer: CMakeFiles/RayTracer.dir/build.make
RayTracer: CMakeFiles/RayTracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable RayTracer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RayTracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracer.dir/build: RayTracer
.PHONY : CMakeFiles/RayTracer.dir/build

CMakeFiles/RayTracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayTracer.dir/clean

CMakeFiles/RayTracer.dir/depend:
	cd /home/trios/Desktop/SEM7/VR/RayTracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/trios/Desktop/SEM7/VR/RayTracer /home/trios/Desktop/SEM7/VR/RayTracer /home/trios/Desktop/SEM7/VR/RayTracer/build /home/trios/Desktop/SEM7/VR/RayTracer/build /home/trios/Desktop/SEM7/VR/RayTracer/build/CMakeFiles/RayTracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayTracer.dir/depend
