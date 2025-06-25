cmake_minimum_required(VERSION 3.29)
project(2DGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add SDL2_image - try different methods
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(SDL2_IMAGE SDL2_image)
endif()

# If pkg-config didn't work, try find_library
if(NOT SDL2_IMAGE_FOUND)
    find_library(SDL2_IMAGE_LIBRARIES
            NAMES SDL2_image
            HINTS /usr/local/lib /opt/homebrew/lib
    )
    find_path(SDL2_IMAGE_INCLUDE_DIRS
            NAMES SDL_image.h
            HINTS /usr/local/include/SDL2 /opt/homebrew/include/SDL2
    )
endif()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(2DGameEngine ${SRC_FILES}
        src/Engine.cpp
        src/InputManager.cpp
        src/GameObject.cpp
        src/Component.cpp
        src/Transform.cpp
        src/TextureManager.cpp
        src/Sprite.cpp
        src/main.cpp
        include/Engine.h
        include/InputManager.h
        include/GameObject.h
        include/Component.h
        include/Transform.h
        include/TextureManager.h
        include/Sprite.h
)

target_include_directories(2DGameEngine PRIVATE include)
target_link_libraries(2DGameEngine ${SDL2_LIBRARIES})

# Link SDL2_image if found
if(SDL2_IMAGE_LIBRARIES)
    target_link_libraries(2DGameEngine ${SDL2_IMAGE_LIBRARIES})
    if(SDL2_IMAGE_INCLUDE_DIRS)
        target_include_directories(2DGameEngine PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    endif()
    message(STATUS "SDL2_image found and linked")
else()
    message(WARNING "SDL2_image not found - image loading will not work")
endif()