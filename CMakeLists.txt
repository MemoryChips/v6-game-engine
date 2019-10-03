cmake_minimum_required(VERSION 3.10)
project(Sandbox VERSION 1.0.0) 

set(CMAKE_CXX_STANDARD 17)

set(SOURCE sandbox/app.cpp)
file(GLOB SOURCES "sandbox/src/*.cpp")

include_directories(sandbox/include)
# TODO: Review these includes likely need them all to include the sub includes of v6.h
# TODO: Can precompiled headers help with this
# this is needed due to log.h including spdlog
include_directories(v6/vendor/spdlog/include)

# for sure need v6 which should be the public api of v6
include_directories(v6 v6/include v6/src)

include_directories(v6/vendor/glfw/include/GLFW v6/vendor/glfw/deps)

include_directories(v6/vendor/imgui/include)
include_directories(v6/vendor/glm)
include_directories(v6/vendor/glad/include)

# for the v6 shared library
add_subdirectory(v6)

add_executable(${PROJECT_NAME} ${SOURCE} ${SOURCES})
# add_executable(${PROJECT_NAME} ${SOURCE} ${TEST_SOURCES})
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(${PROJECT_NAME} PRIVATE V6_DEMO_VERSION="${PROJECT_VERSION}")
target_link_libraries(${PROJECT_NAME} v6)
