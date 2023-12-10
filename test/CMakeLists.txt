# Set library directory
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)

# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})

# Set test source files
set(TEST_SOURCES
    test1.c
)

# Add an executable for tests
add_executable(test_executable ${TEST_SOURCES})

# Include directories for tests
target_include_directories(test_executable PRIVATE ${LIB_DIR}/Unity)

# Link Unity library with test executable
target_link_libraries(test_executable PRIVATE unity)

# Optionally, set output directories for test files
set_target_properties(test_executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
)

# Add tests
enable_testing()
add_test(NAME my_tests COMMAND test_executable)