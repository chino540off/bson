cmake_minimum_required(VERSION 2.8)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -fprofile-arcs -ftest-coverage")

add_executable(bson ../src/main.cc)

