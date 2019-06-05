# for glad loader
cmake_minimum_required(VERSION 3.10)

# project(glad VERSION 1.0.0) 

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_SOURCES "src/glad.c")
include_directories(include)
add_library(glad ${LIB_SOURCES})
