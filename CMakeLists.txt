cmake_minimum_required(VERSION 3.9.1)
project(DSA_Vedant_Mathur)

#set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
#set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCES src/*.c)
set(SOURCES ${SOURCES})

add_executable(dsa_driver bin/driver.c)

add_library(binary_tree SHARED ${SOURCES})





