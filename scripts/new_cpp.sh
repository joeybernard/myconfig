# Create directories
mkdir bin build config include lib src

# Create a hello world
cat <<EOF >src/main.cpp
#include <cstdio>
#include "Config.h"

int main(int argc, char* argv[]) {
    // output program location and version
    printf("Running: %s\nVersion: %i.%i\n", argv[argc-argc],
        VERSION_MAJOR, VERSION_MINOR);
    printf("Hello CMake!\n");
    return 0;
}
EOF

# Create a Config.h base file
cat <<EOF >include/Config.h.in
#pragma once
#define VERSION_MAJOR @Boilerplate_VERSION_MAJOR@
#define VERSION_MINOR @Boilerplate_VERSION_MINOR@
EOF

# Create a cmake file for building
cat <<EOF >CMakeLists.txt
# Specify the minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(Boilerplate VERSION 1.0)

# Request C++ 11 standard features
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(include/Config.h.in
    "\${CMAKE_CURRENT_SOURCE_DIR}/include/Config.h")

# Compile the passed source files into an executable 
add_executable(Boilerplate 
    "\${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
target_include_directories(Boilerplate PUBLIC
    "\${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set the output directory for executables
set_target_properties(Boilerplate
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "\${PROJECT_SOURCE_DIR}/bin")

target_compile_features(Boilerplate PUBLIC cxx_std_11)

# add compiler warning flags just when building this project
# via the BUILD_INTERFACE generator expression
set(gcc_like_cxx "\$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "\$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wformat=2")
set(msvc_flags "-W3")

target_compile_options(Boilerplate PRIVATE
    "\$<\${gcc_like_cxx}:\$<BUILD_INTERFACE:\${gcc_flags}>>"
    "\$<\${msvc_cxx}:\$<BUILD_INTERFACE:\${msvc_flags}>>")
EOF

