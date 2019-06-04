cmake_minimum_required(VERSION 3.10)
project(Sandbox VERSION 1.0.0) # TODO: set define with version and log it

set(CMAKE_CXX_STANDARD 17)

set(SOURCE sandbox/app.cpp)

include_directories(v6/vendor/spdlog/include)
include_directories(v6/include v6/src)
include_directories(v6/vendor/glfw/include/GLFW v6/vendor/glfw/deps)

include_directories(v6/vendor/imgui/include)
include_directories(v6/vendor/glm)
include_directories(v6/vendor/glad/include)

# for the v6 shared library
add_subdirectory(v6)

# FIXME: fix this define
# set(V6_DEMO_VERSION "-DV6_DEMO_VERSION ${PROJECT_VERSION}")
# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${V6_DEMO_VERSION}")

add_executable(${PROJECT_NAME} ${SOURCE} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} v6)
