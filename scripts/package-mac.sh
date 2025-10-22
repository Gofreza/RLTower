#!/bin/bash

echo "Building MacOs executable..."

rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -- -j$(sysctl -n hw.ncpu)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful! Creating distribution package..."
