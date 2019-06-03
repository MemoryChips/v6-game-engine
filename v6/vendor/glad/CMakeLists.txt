# for glad loader
cmake_minimum_required(VERSION 3.10)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_SOURCES "src/glad.c")
include_directories(include)
add_library(glad ${LIB_SOURCES})
