#!/bin/bash
# Builds everything (engine demo, Pong, Breakout) via CMake.
set -e
cd "$(dirname "$0")"

cmake -S . -B build
cmake --build build

echo ""
echo "Build successful! Binaries are in ./build:"
echo "  ./build/2DGameEngine   (bare engine demo)"
echo "  ./build/Pong"
echo "  ./build/Breakout"
