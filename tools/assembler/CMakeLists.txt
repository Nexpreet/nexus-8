add_executable(nexus_asm
    asm_main.c
)

target_link_libraries(nexus_asm
    PRIVATE nexus_core
)

target_include_directories(nexus_asm
    PRIVATE ${CMAKE_SOURCE_DIR}/core/include
)
