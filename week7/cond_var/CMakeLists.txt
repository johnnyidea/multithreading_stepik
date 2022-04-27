cmake_minimum_required(VERSION 3.20)
project(cond_var)


set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread")

add_executable(cond_var main.cpp)
