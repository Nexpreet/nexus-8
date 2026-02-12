enable_testing()

add_executable(nexus_tests
    test_main.c
)

target_link_libraries(nexus_tests
    PRIVATE nexus_core
)

add_test(NAME nexus_tests COMMAND nexus_tests)
