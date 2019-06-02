cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

file(GLOB V6_LIB_SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
include_directories(include src)
include_directories(vendor/spdlog/include)
include_directories(vendor/glm)
include_directories(vendor/imgui/include)

# for imgui lib
add_subdirectory(vendor/imgui)

# for glad loader
add_subdirectory(vendor/glad)

# for glfw3 library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

add_library(v6 SHARED ${V6_LIB_SOURCES})
target_link_libraries(v6 glad glfw imgui)
