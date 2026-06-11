#!/bin/bash
# Builds just the Breakout example via CMake.
set -e
cd "$(dirname "$0")"

cmake -S . -B build
cmake --build build --target Breakout

echo ""
echo "Build successful! Run ./build/Breakout to play."
