#!/bin/bash

# Get the absolute path of the project root directory
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

# Check if build directory exists
if [ ! -d "${PROJECT_ROOT}/build" ]; then
    echo "Error: Build directory not found. Please build the project first."
    exit 1
fi

# Check if build/bin directory exists
if [ ! -d "${PROJECT_ROOT}/build/bin" ]; then
    echo "Error: No bin directory found. Please build the project first."
    exit 1
fi

# Navigate to build directory
cd "${PROJECT_ROOT}/build"

# Check if 7-Zip is installed
if command -v 7z &> /dev/null; then
    echo "Creating archive..."
    7z a -tzip StelarOrbit.zip bin/*
    echo "Created StelarOrbit.zip in build folder"
else
    echo "Error: Please install 7-Zip to create the archive"
    exit 1
fi

cd .. 