cmake_minimum_required(VERSION 3.20)
project(Course_project)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(CMAKE_CXX_STANDARD 20)

add_executable(Course_project main.cpp Mytemplate.cpp Bit_number.h Keccak.cpp Keccak.h RSA.cpp RSA.h Bit_number.cpp)
