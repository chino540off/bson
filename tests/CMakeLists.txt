cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -fprofile-arcs -ftest-coverage")

enable_testing()

add_executable(test001 test001.cc)
add_test(test001 ./test001)
add_executable(test002 test002.cc)
add_test(test002 ./test002)
