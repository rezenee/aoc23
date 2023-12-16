cmake_minimum_required(VERSION 3.10)  # Set the minimum required version of cmake

project(10)  # Name your project

# Set the C++ compiler flags
# Note: CMake has its own defaults and also considers the CMAKE_BUILD_TYPE
# for setting flags for Debug, Release, etc.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# Define the executable target p1 and its source file
add_executable(p1 p1.cpp)

# Define the executable target p2 and its source file
add_executable(p2 p2.cpp)