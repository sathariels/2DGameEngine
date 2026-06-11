cmake_minimum_required(VERSION 3.16)
project(2DGameEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ------------------------------------------------------
find_package(SDL2 REQUIRED)

# Prefer the SDL2_ttf CMake package (vcpkg, recent Homebrew, most Linux
# distros); fall back to a plain library search otherwise.
find_package(SDL2_ttf QUIET CONFIG)
if(TARGET SDL2_ttf::SDL2_ttf)
    set(SDL2_TTF_LIBRARY SDL2_ttf::SDL2_ttf)
else()
    find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf REQUIRED)
endif()

if(TARGET SDL2::SDL2)
    set(SDL2_LIBRARY SDL2::SDL2)
else()
    set(SDL2_LIBRARY ${SDL2_LIBRARIES})
endif()

# --- Engine library ----------------------------------------------------
set(ENGINE_SOURCES
    src/Engine.cpp
    src/InputManager.cpp
    src/GameObject.cpp
    src/Component.cpp
    src/Transform.cpp
    src/TextureManager.cpp
    src/FontManager.cpp
    src/Sprite.cpp
    src/Text.cpp
    src/Rigidbody.cpp
    src/Collider.cpp
    src/Physics.cpp
)

add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC include ${SDL2_INCLUDE_DIRS})
target_link_libraries(engine PUBLIC ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

# --- Executables -------------------------------------------------------
add_executable(2DGameEngine src/main.cpp)
target_link_libraries(2DGameEngine PRIVATE engine)

add_executable(Pong examples/Pong.cpp)
target_link_libraries(Pong PRIVATE engine)

add_executable(Breakout examples/Breakout.cpp)
target_link_libraries(Breakout PRIVATE engine)

# Standalone OO-vs-ECS benchmark (no SDL needed)
add_executable(ecs_benchmark experiments/ecs_benchmark.cpp)
target_compile_options(ecs_benchmark PRIVATE -O2)
