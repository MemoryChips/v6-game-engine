# for imgui
cmake_minimum_required(VERSION 3.10)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
file(GLOB LIB_SOURCES "src/*.cpp")
include_directories(include ../glfw/include)
add_library(imgui ${LIB_SOURCES})
