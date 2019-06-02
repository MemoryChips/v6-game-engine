cmake_minimum_required(VERSION 3.10)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

# set(SOURCE main.cpp src/hello.cpp)
set(SOURCE sandbox/app.cpp)
# include_directories(my-opengl/include tests) 
include_directories(vendor/spdlog/include)
include_directories(v6/include v6/src)
include_directories(v6/vendor/glfw/include/GLFW v6/vendor/glfw/deps)

include_directories(v6/vendor/imgui/include)
include_directories(v6/vendor/glm)
include_directories(v6/vendor/glad/include)

# for the v6 shared library
add_subdirectory(v6)

# file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} v6)
# important that my-opengl comes first. Why?
# target_link_libraries(${PROJECT_NAME} my-opengl imgui glad glfw)
# target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})
