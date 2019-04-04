cmake_minimum_required(VERSION 3.13)
project(lottery)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_executable(lottery main.cpp ${SOURCES})