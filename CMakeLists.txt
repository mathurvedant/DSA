cmake_minimum_required(VERSION 3.9.1)
project(DSA_Vedant_Mathur)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

set(SOURCES src/binary_tree.c)

add_library(binary_tree SHARED ${SOURCES})





