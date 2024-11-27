cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet une seule fois
project(StelarOrbit LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Configuration de SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

# Ajout de l'exécutable
add_executable(StelarOrbit src/main.cpp
    src/CelestialBody.cpp
    src/Star.cpp
    src/Planet.cpp
    src/Satellite.cpp
    src/SolarSystem.cpp
)

# Lier SFML et configurer les include directories
target_link_libraries(StelarOrbit PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

# Spécifier le standard C++ et inclure le dossier d'en-tête
target_compile_features(StelarOrbit PRIVATE cxx_std_17)
target_include_directories(StelarOrbit PRIVATE include)

# S'assurer que les DLLs de SFML sont copiées près de l'exécutable
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET StelarOrbit POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:StelarOrbit>
    )
endif()