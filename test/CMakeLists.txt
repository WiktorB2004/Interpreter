# Set library directory
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
# Set test directory
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)
# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})

# Define a function to add test executables
function(add_test_executable TARGET_NAME SOURCE_DIR)
    # Set test source files for the given target
    set(TEST_SOURCES
        ${TEST_DIR}/${SOURCE_DIR}/sample.c
    )
    # Add an executable for the test
    add_executable(${TARGET_NAME} ${TEST_SOURCES})
    # Include directories for the test
    target_include_directories(${TARGET_NAME} PRIVATE ${LIB_DIR}/Unity)
    # Link Unity library with the test executable
    target_link_libraries(${TARGET_NAME} PRIVATE unity)
    # Set output directories for test files
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${SOURCE_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/${SOURCE_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/${SOURCE_DIR}
    )
    # Add test
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

# Define test executables using the function
set(TESTS
    lexer_test
    parser_test
    interpreter_test
    utils_test
)
foreach(TEST ${TESTS})
    add_test_executable(test_${TEST} ${TEST})
endforeach()

# Enable testing
enable_testing()
