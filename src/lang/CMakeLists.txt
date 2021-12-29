cmake_minimum_required(VERSION 3.10)

# Project Name
project(New_Lang VERSION 1.0.0)

# Group together the source files
file(GLOB SOURCE lexer.cpp parser.cpp error_handler.cpp test.cpp)

# Specify where the header files are (In the current directory)
include_directories(${PROJECT_SOURCE_DIR})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -c")

# Executable storage location (In the current directory)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# Add the executable
add_executable(a.out ${SOURCE})

