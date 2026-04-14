#!/bin/bash
echo "Building Breakout..."
mkdir -p build_manual

SRC_FILES=$(ls src/*.cpp | grep -v "main.cpp")

clang++ -std=c++20 \
    -I include \
    -I /opt/homebrew/include \
    -L /opt/homebrew/lib \
    -Wl,-rpath,/opt/homebrew/lib \
    -lSDL2 -lSDL2_ttf \
    $SRC_FILES \
    examples/Breakout.cpp \
    -o build_manual/Breakout

if [ $? -eq 0 ]; then
    echo "Build successful! Run ./build_manual/Breakout to play."
else
    echo "Build failed."
    exit 1
fi
