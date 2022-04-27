cmake_minimum_required(VERSION 3.20)

project(thread_posix)

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")

add_executable(thread_posix main.cpp)

#target_link_libraries(-lpthread)

