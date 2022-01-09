cmake_minimum_required(VERSION 3.10)

# Project Name
project(New_Lang VERSION 1.0.0)

# Group together the source files
file(GLOB SOURCE src/*.cpp src/nodes/*.cpp)

# Specify where the header files are (In the current directory)
include_directories(${PROJECT_SOURCE_DIR})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -c")  # Perhaps doesn't work?
set(CMAKE_BUILD_TYPE Debug)

# Executable storage location (In the current directory)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# Add the executable
add_executable(a.out ${SOURCE})

