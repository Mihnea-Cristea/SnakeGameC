cmake_minimum_required(VERSION 3.5)
project(Snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Weffc++ -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(Snake ${SOURCE_FILES})