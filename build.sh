#!/bin/bash
echo "Building 2D Game Engine..."
mkdir -p build_manual

# Compile with clang++
# -std=c++20: Use C++20 standard
# -I include: Add project include directory
# -I /opt/homebrew/include: Add Homebrew include directory (for SDL2)
# -L /opt/homebrew/lib: Add Homebrew lib directory
# -lSDL2: Link against SDL2
# -rpath ...: Ensure the executable can find the dylib at runtime

clang++ -std=c++20 \
    -I include \
    -I /opt/homebrew/include \
    -L /opt/homebrew/lib \
    -Wl,-rpath,/opt/homebrew/lib \
    -lSDL2 \
    src/*.cpp \
    -o build_manual/2DGameEngine

if [ $? -eq 0 ]; then
    echo "Build successful! Run ./build_manual/2DGameEngine to start."
else
    echo "Build failed."
    exit 1
fi
