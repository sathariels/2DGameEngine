#!/bin/bash
echo "Building Pong..."
mkdir -p build_manual

# Compile Engine source files BUT EXCLUDE src/main.cpp
# We use examples/Pong.cpp as the main entry point

# Get all source files except main.cpp
SRC_FILES=$(ls src/*.cpp | grep -v "main.cpp")

clang++ -std=c++20 \
    -I include \
    -I /opt/homebrew/include \
    -L /opt/homebrew/lib \
    -Wl,-rpath,/opt/homebrew/lib \
    -lSDL2 \
    $SRC_FILES \
    examples/Pong.cpp \
    -o build_manual/Pong

if [ $? -eq 0 ]; then
    echo "Build successful! Run ./build_manual/Pong to play."
else
    echo "Build failed."
    exit 1
fi
