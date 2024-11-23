# Toolchain file for cross-compiling to Windows with MinGW on macOS

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross-compiler
set(CMAKE_C_COMPILER /opt/homebrew/Cellar/mingw-w64/12.0.0_1/toolchain-x86_64/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/mingw-w64/12.0.0_1/toolchain-x86_64/bin/x86_64-w64-mingw32-g++)
