cmake_minimum_required(VERSION 3.15)
project(Shard VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files from src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(shard ${SOURCES})

# Include directories
target_include_directories(shard PRIVATE include)

# Set output directory
set_target_properties(shard PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# Configure
#cmake -B build -G "Visual Studio 17 2022"

# Build
#cmake --build build --config Release