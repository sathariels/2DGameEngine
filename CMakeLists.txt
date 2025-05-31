
cmake_minimum_required(VERSION 3.29)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(2DGameEngine ${SRC_FILES}
        src/Engine.cpp
        src/InputManager.cpp
        include/Engine.h
        include/InputManager.h
)
target_include_directories(2DGameEngine PRIVATE include)
target_link_libraries(2DGameEngine ${SDL2_LIBRARIES})
target_include_directories(2DGameEngine PRIVATE include)
