cmake_minimum_required(VERSION 3.16)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include directories
include_directories(include)

# Define source files explicitly
set(SRC_FILES
    src/Engine.cpp
    src/InputManager.cpp
    src/GameObject.cpp
    src/Component.cpp
    src/Transform.cpp
    src/TextureManager.cpp
    src/Sprite.cpp
    src/Rigidbody.cpp
    src/Collider.cpp
    src/Physics.cpp
    src/main.cpp
)

# Header files (for IDE visibility)
set(HEADER_FILES
    include/Engine.h
    include/InputManager.h
    include/GameObject.h
    include/Component.h
    include/Transform.h
    include/TextureManager.h
    include/Sprite.h
    include/Rigidbody.h
    include/Collider.h
    include/Physics.h
)

add_executable(2DGameEngine ${SRC_FILES} ${HEADER_FILES})

target_include_directories(2DGameEngine PRIVATE include)
target_link_libraries(2DGameEngine ${SDL2_LIBRARIES})