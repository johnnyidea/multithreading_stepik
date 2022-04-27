cmake_minimum_required(VERSION 3.20)
project(mutex)

set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread")

add_executable(mutex main.cpp)
