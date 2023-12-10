# Set library directory
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

# Set test dir
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)

# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})


# Set test source files
set(LEXER_TEST_SOURCES
    ${TEST_DIR}/lexer_test/sample.c
)

set(PARSER_TEST_SOURCES
    ${TEST_DIR}/parser_test/sample.c
)

set(INTERPRETER_TEST_SOURCES
    ${TEST_DIR}/interpreter_test/sample.c
)

set(UTILS_TEST_SOURCES
    ${TEST_DIR}/utils_test/sample.c
)

# Add an executable for tests
add_executable(test_lexer ${LEXER_TEST_SOURCES})
add_executable(test_parser ${PARSER_TEST_SOURCES})
add_executable(test_interpreter ${INTERPRETER_TEST_SOURCES})
add_executable(test_utils ${UTILS_TEST_SOURCES})

# Include directories for tests
target_include_directories(test_lexer PRIVATE ${LIB_DIR}/Unity)
target_include_directories(test_parser PRIVATE ${LIB_DIR}/Unity)
target_include_directories(test_interpreter PRIVATE ${LIB_DIR}/Unity)
target_include_directories(test_utils PRIVATE ${LIB_DIR}/Unity)

# Link Unity library with test executable
target_link_libraries(test_lexer PRIVATE unity)
target_link_libraries(test_parser PRIVATE unity)
target_link_libraries(test_interpreter PRIVATE unity)
target_link_libraries(test_utils PRIVATE unity)

# Optionally, set output directories for test files
set_target_properties(test_lexer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/lexer
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/lexer
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/lexer
)
set_target_properties(test_parser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/parser
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/parser
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/parser
)
set_target_properties(test_interpreter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/interpreter
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/interpreter
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/interpreter
)
set_target_properties(test_utils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/utils
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/utils
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj/utils
)

# Add tests
enable_testing()
add_test(NAME lexer COMMAND test_lexer)
add_test(NAME parser COMMAND test_parser)
add_test(NAME interpreter COMMAND test_interpreter)
add_test(NAME utils COMMAND test_utils)