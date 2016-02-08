cmake_minimum_required(VERSION 2.8)

include(CTest)
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
INCLUDE(Dart)

enable_testing()

add_executable(test001 test001.cc)
add_test(test001 ./test001)
