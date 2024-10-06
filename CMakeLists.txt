cmake_minimum_required(VERSION 3.9.1)
project(DSA_Vedant_Mathur)

set(CMAKE_CXX_STANDARD 14)

message(${CMAKE_BINARY_DIR})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SOURCES include/binary_tree.h src/binary_tree.c)

add_library(bt ${SOURCES})





