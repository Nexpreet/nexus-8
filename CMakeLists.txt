cmake_minimum_required(VERSION 3.20)

project(nexus8 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default build type (CLion usually sets this, but this helps outside CLion)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Warnings (good hygiene)
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wstrict-prototypes
)

# Debug helpers: sanitizers
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -g3 -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
else()
    add_compile_options(-O3)
endif()

# Enable CTest integration
include(CTest)

add_subdirectory(core)
add_subdirectory(tests)

# Tools (enable once you create the folder/files)
add_subdirectory(tools/assembler)
