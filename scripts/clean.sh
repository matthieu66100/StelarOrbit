#!/bin/bash

# Get the absolute path of the project root directory
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

# Verify we're in the correct directory
if [ ! -f "${PROJECT_ROOT}/CMakeLists.txt" ]; then
    echo "Error: CMakeLists.txt not found. Make sure you're in the project directory."
    exit 1
fi

# Check if build directory exists
if [ ! -d "${PROJECT_ROOT}/build" ]; then
    echo "Build directory doesn't exist. Nothing to clean."
    exit 0
fi

# Clean only the build directory content
echo "Cleaning build directory..."
find "${PROJECT_ROOT}/build" -mindepth 1 -delete
echo "Build directory cleaned" 