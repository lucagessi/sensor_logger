# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/luca/Documents/Embedded/sensor_logger/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luca/Documents/Embedded/sensor_logger/test

# Include any dependencies generated for this target.
include CMakeFiles/runTests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/runTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/runTests.dir/flags.make

CMakeFiles/runTests.dir/src/SerialTests.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/src/SerialTests.cpp.o: src/SerialTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/runTests.dir/src/SerialTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/src/SerialTests.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/test/src/SerialTests.cpp

CMakeFiles/runTests.dir/src/SerialTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/src/SerialTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/test/src/SerialTests.cpp > CMakeFiles/runTests.dir/src/SerialTests.cpp.i

CMakeFiles/runTests.dir/src/SerialTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/src/SerialTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/test/src/SerialTests.cpp -o CMakeFiles/runTests.dir/src/SerialTests.cpp.s

CMakeFiles/runTests.dir/src/MainTests.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/src/MainTests.cpp.o: src/MainTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/runTests.dir/src/MainTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/src/MainTests.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/test/src/MainTests.cpp

CMakeFiles/runTests.dir/src/MainTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/src/MainTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/test/src/MainTests.cpp > CMakeFiles/runTests.dir/src/MainTests.cpp.i

CMakeFiles/runTests.dir/src/MainTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/src/MainTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/test/src/MainTests.cpp -o CMakeFiles/runTests.dir/src/MainTests.cpp.s

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o: /home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp > CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.i

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp -o CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.s

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o: /home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp > CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.i

CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp -o CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.s

CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o: src/CommandsInterpreterTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/test/src/CommandsInterpreterTests.cpp

CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/test/src/CommandsInterpreterTests.cpp > CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.i

CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/test/src/CommandsInterpreterTests.cpp -o CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.s

CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o: CMakeFiles/runTests.dir/flags.make
CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o: src/AccelerometerTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o -c /home/luca/Documents/Embedded/sensor_logger/test/src/AccelerometerTests.cpp

CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luca/Documents/Embedded/sensor_logger/test/src/AccelerometerTests.cpp > CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.i

CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luca/Documents/Embedded/sensor_logger/test/src/AccelerometerTests.cpp -o CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.s

# Object files for target runTests
runTests_OBJECTS = \
"CMakeFiles/runTests.dir/src/SerialTests.cpp.o" \
"CMakeFiles/runTests.dir/src/MainTests.cpp.o" \
"CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o" \
"CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o" \
"CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o" \
"CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o"

# External object files for target runTests
runTests_EXTERNAL_OBJECTS =

runTests: CMakeFiles/runTests.dir/src/SerialTests.cpp.o
runTests: CMakeFiles/runTests.dir/src/MainTests.cpp.o
runTests: CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/Serial.cpp.o
runTests: CMakeFiles/runTests.dir/home/luca/Documents/Embedded/sensor_logger/src/AccelerometerSensor.cpp.o
runTests: CMakeFiles/runTests.dir/src/CommandsInterpreterTests.cpp.o
runTests: CMakeFiles/runTests.dir/src/AccelerometerTests.cpp.o
runTests: CMakeFiles/runTests.dir/build.make
runTests: /usr/lib/x86_64-linux-gnu/libgtest.a
runTests: CMakeFiles/runTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable runTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/runTests.dir/build: runTests

.PHONY : CMakeFiles/runTests.dir/build

CMakeFiles/runTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/runTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/runTests.dir/clean

CMakeFiles/runTests.dir/depend:
	cd /home/luca/Documents/Embedded/sensor_logger/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luca/Documents/Embedded/sensor_logger/test /home/luca/Documents/Embedded/sensor_logger/test /home/luca/Documents/Embedded/sensor_logger/test /home/luca/Documents/Embedded/sensor_logger/test /home/luca/Documents/Embedded/sensor_logger/test/CMakeFiles/runTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/runTests.dir/depend

