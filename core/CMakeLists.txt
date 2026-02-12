add_library(nexus_core
    src/cpu.c
)

target_include_directories(nexus_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
