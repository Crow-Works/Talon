#!/bin/bash

# Go to the Talon root directory
cd "$(dirname "$0")"

# Define paths
TALON_DIR=$(pwd)
BUILD_DIR="$TALON_DIR/build"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Run CMake to generate build files
cmake -B "$BUILD_DIR" -G Ninja "$TALON_DIR"

# Check if CMake ran successfully
if [ $? -ne 0 ]; then
    echo "Error: Failed to run CMake."
    exit 1
fi

# Run the build system (e.g., Ninja or make) to compile the project
cmake --build "$BUILD_DIR"

# Check if the build succeeded
if [ $? -ne 0 ]; then
    echo "Error: Failed to build Talon package manager."
    exit 1
fi

mv build/Talon .
mv build/compile_commands.json .

echo "Talon package manager built successfully."
exit 0


