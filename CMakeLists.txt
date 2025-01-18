cmake_minimum_required(VERSION 3.9.1)
project(DSA_Vedant_Mathur)

#set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
#set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.c src/*.cpp)
set(SOURCES ${SOURCES})

add_library(dsa SHARED ${SOURCES})

add_executable(dsa_driver bin/dsa_driver.c)
target_link_libraries(dsa_driver dsa)

add_executable(algos_driver bin/algos_driver.c)
target_link_libraries(algos_driver dsa)

add_executable(dsa_cpp_driver bin/dsa_cpp_driver.cpp)
target_link_libraries(dsa_cpp_driver dsa)





