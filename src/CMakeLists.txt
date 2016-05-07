cmake_minimum_required(VERSION 3.0)
project(myVector)
set( mv_source ./myVector.cpp )
add_library( myVector STATIC ${mv_source} )
