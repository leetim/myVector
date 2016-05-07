cmake_minimum_required(VERSION 3.0)

project(myVector)
add_definitions(-Wall -ansi -pthread)
set(CMAKE_EXE_LINKER_FLAGS "-pthread -std=c++11")

enable_testing()

include_directories(./include)

add_subdirectory(src ./src)
add_subdirectory(test ./test)
