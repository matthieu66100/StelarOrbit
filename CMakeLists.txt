cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet une seule fois
project(Cartagene LANGUAGES CXX)

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
add_executable(main src/main.cpp)

# Lier SFML et configurer les include directories
target_link_libraries(main PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
)

# Spécifier le standard C++
target_compile_features(main PRIVATE cxx_std_17)

# S'assurer que les DLLs de SFML sont copiées près de l'exécutable
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:main>
    )
endif()