cmake_minimum_required(VERSION 3.10)
project(Sandbox VERSION 1.0.0) 

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

add_executable(${PROJECT_NAME} ${SOURCE} ${TEST_SOURCES})
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(${PROJECT_NAME} PRIVATE V6_DEMO_VERSION="${PROJECT_VERSION}")
target_link_libraries(${PROJECT_NAME} v6)
