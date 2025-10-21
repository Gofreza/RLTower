#!/bin/bash

echo "Building Windows executable..."

# Create/clean build directory
rm -rf build-win
mkdir -p build-win
cd build-win
mkdir -p bin

# Configure and build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake ..
make -j$(sysctl -n hw.ncpu)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

cd ..

echo "Build successful! Creating distribution package..."

# Copy executable
mv build-win/RLTower.exe build-win/bin/

# Copy MinGW runtime DLLs
cp /opt/homebrew/Cellar/mingw-w64/13.0.0_2/toolchain-x86_64/x86_64-w64-mingw32/lib/libgcc_s_seh-1.dll build-win/bin/
cp /opt/homebrew/Cellar/mingw-w64/13.0.0_2/toolchain-x86_64/x86_64-w64-mingw32/lib/libstdc++-6.dll build-win/bin/
cp /opt/homebrew/Cellar/mingw-w64/13.0.0_2/toolchain-x86_64/x86_64-w64-mingw32/bin/libwinpthread-1.dll build-win/bin/

# Copy SDL2 DLLs (this will copy ALL DLLs including dependencies)
cp ~/Documents/cross-compile/windows-libs/SDL2-2.32.10/x86_64-w64-mingw32/bin/*.dll build-win/bin/
cp ~/Documents/cross-compile/windows-libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/bin/*.dll build-win/bin/
cp ~/Documents/cross-compile/windows-libs/SDL2_image-2.8.8/x86_64-w64-mingw32/bin/*.dll build-win/bin/

# Copy game assets
cp -r res build-win/

# Create README
cat > build-win/README.txt << EOF
RLTower
=========

How to run:
- Open the 'bin' folder
- Double-click RLTower.exe

Requirements:
- Windows 7 or later
- 64-bit system

EOF

# Create ZIP
cd build-win
zip -r ../RLTower-Windows.zip .
cd ..

echo "Package created: RLTower-Windows.zip"