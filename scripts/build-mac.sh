#!/bin/bash

set -e  # exit immediately if a command fails

BUILD_DIR="build"

echo "🔨 Starting build..."

# Create build directory if it doesn’t exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
    cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug
fi

# Build the project using all CPU cores
cmake --build "$BUILD_DIR" --config Debug -- -j"$(sysctl -n hw.ncpu)"

echo "✅ Build complete!"
