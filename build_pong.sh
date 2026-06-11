#!/bin/bash
# Builds just the Pong example via CMake.
set -e
cd "$(dirname "$0")"

cmake -S . -B build
cmake --build build --target Pong

echo ""
echo "Build successful! Run ./build/Pong to play."
