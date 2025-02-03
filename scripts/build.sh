#!/bin/bash

# Get the absolute path of the project root directory
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

# Create build directory if it doesn't exist
if [ ! -d "${PROJECT_ROOT}/build" ]; then
    echo "Creating build directory..."
    mkdir "${PROJECT_ROOT}/build"
fi

# Navigate to build directory and run cmake
cd "${PROJECT_ROOT}/build"
cmake ..
cmake --build .
echo "Build completed"
cd .. 