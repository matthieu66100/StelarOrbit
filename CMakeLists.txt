cmake_minimum_required(VERSION 3.10)

# Define project name
project(StelarOrbit LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# SFML Configuration
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

# Add executable
add_executable(StelarOrbit src/main.cpp
    src/CelestialBody.cpp
    src/Star.cpp
    src/Planet.cpp
    src/Satellite.cpp
    src/SolarSystem.cpp
    src/TextDisplay.cpp
)

# Link SFML and configure include directories
target_link_libraries(StelarOrbit PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

# Specify C++ standard and include directory
target_compile_features(StelarOrbit PRIVATE cxx_std_17)
target_include_directories(StelarOrbit PRIVATE include)

# Copy resources folder
file(COPY ${CMAKE_SOURCE_DIR}/ressources DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Ensure SFML DLLs are copied near executable
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET StelarOrbit POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:StelarOrbit>
    )
endif()