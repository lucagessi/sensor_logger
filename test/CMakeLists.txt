cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(inc)
include_directories(../inc)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests src/SerialTests.cpp src/MainTests.cpp ../src/Serial.cpp ../src/AccelerometerSensor.cpp src/CommandsInterpreterTests.cpp src/AccelerometerTests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)