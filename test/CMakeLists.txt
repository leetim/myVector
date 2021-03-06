cmake_minimum_required(VERSION 3.0)

project(tests)
add_definitions(-Wall -ansi -pthread -std=c++11 --coverage -Wall)
# set( CMAKE_CXX_FLAGS "-O0 -Wall -pedantic -ansi -std=c++11 --coverage" )
set(CMAKE_EXE_LINKER_FLAGS "-pthread --coverage")

add_library(gtest STATIC IMPORTED)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/gtestLib/libgtest.a)
add_library(gtest_main STATIC IMPORTED)
set_property(TARGET gtest_main PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/gtestLib/libgtest_main.a)
add_library(gmock STATIC IMPORTED)
set_property(TARGET gmock PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/gtestLib/libgmock.a)
add_library(gmock_main STATIC IMPORTED)
set_property(TARGET gmock_main PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/gtestLib/libgmock_main.a)

include_directories(./gtestInclude)

add_executable(test1 test.cpp)
target_link_libraries(test1 gtest gtest_main gmock gmock_main myVector)
add_executable(test2 test2.cpp)
target_link_libraries(test2 gtest gtest_main gmock gmock_main myVector)
add_executable(test3 test3.cpp)
target_link_libraries(test3 gtest gtest_main gmock gmock_main myVector)
add_executable(test4 test4.cpp)
target_link_libraries(test4 gtest gtest_main gmock gmock_main myVector)
add_executable(test5 test5.cpp)
target_link_libraries(test5 gtest gtest_main gmock gmock_main myVector)
add_executable(sort_test sort_test.cpp)
target_link_libraries(sort_test gtest gtest_main gmock gmock_main myVector)
add_executable(str_test str_test.cpp)
target_link_libraries(str_test gtest gtest_main gmock gmock_main myVector)

add_test(NAME Alloc_Test COMMAND test1)
add_test(NAME Vector_Test_Int COMMAND test2)
add_test(NAME Vector_Test_Some COMMAND test3)
add_test(NAME Vector_with_myAlloc COMMAND test4)
add_test(NAME Vector_speed COMMAND test5)
add_test(NAME Sort_test COMMAND sort_test)
add_test(NAME String_test COMMAND str_test)
