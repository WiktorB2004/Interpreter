# Set directory shortcuts
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(UTILS_DIR ${CMAKE_SOURCE_DIR}/utils)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Include main header files
include_directories(${INCLUDE_DIR})

# Set Unity source files
set(UNITY_SOURCES
    ${LIB_DIR}/Unity/unity.c
    ${LIB_DIR}/Unity/unity.h
    ${LIB_DIR}/Unity/unity_internals.h
)

# Add the Unity source files to your project
add_library(unity STATIC ${UNITY_SOURCES})

# Link each test suite header files
include_directories(${TEST_DIR}/lexer_test/include)
include_directories(${TEST_DIR}/parser_test/include)
include_directories(${TEST_DIR}/interpreter_test/include)
include_directories(${TEST_DIR}/utils_test/include)

# Set all test suites source files
set(LEXER_TEST_SOURCES
    ${UTILS_DIR}/lexer_utils.c
    ${SOURCE_DIR}/lexer.c
    ${TEST_DIR}/lexer_test/src/lexer_edge_cases.c
    ${TEST_DIR}/lexer_test/src/lexer_tokens.c
    ${TEST_DIR}/lexer_test/src/lexer_common_combinations.c
)

set(PARSER_TEST_SOURCES
    ${UTILS_DIR}/lexer_utils.c
    ${SOURCE_DIR}/lexer.c
    ${SOURCE_DIR}/parser.c
    ${UTILS_DIR}/ASTNode_Stack.c
    ${TEST_DIR}/parser_test/src/parser_edge_cases.c
    ${TEST_DIR}/parser_test/src/parser_common_combinations.c
)

set(INTERPRETER_TEST_SOURCES
    ${UTILS_DIR}/ASTNode_Stack.c
    ${UTILS_DIR}/expression_eval.c
    ${UTILS_DIR}/memory.c
    ${SOURCE_DIR}/parser.c
    ${SOURCE_DIR}/interpreter.c
    ${TEST_DIR}/interpreter_test/src/interpreter_edge_cases.c
)

set(UTILS_TEST_SOURCES
    ${SOURCE_DIR}/lexer.c
    ${SOURCE_DIR}/parser.c
    ${SOURCE_DIR}/interpreter.c
    ${UTILS_DIR}/ASTNode_Stack.c
    ${UTILS_DIR}/load_code.c
    ${UTILS_DIR}/lexer_utils.c
    ${UTILS_DIR}/expression_eval.c
    ${UTILS_DIR}/memory.c
    ${TEST_DIR}/utils_test/src/utils_edge_cases.c
)

# Include Unity
include_directories(${LIB_DIR}/Unity)

# Add an executable for tests
add_executable(test_lexer ${TEST_DIR}/lexer_test/lexer_test.c ${LEXER_TEST_SOURCES})
add_executable(test_parser ${TEST_DIR}/parser_test/parser_test.c ${PARSER_TEST_SOURCES})
add_executable(test_interpreter ${TEST_DIR}/interpreter_test/interpreter_test.c ${INTERPRETER_TEST_SOURCES})
add_executable(test_utils ${TEST_DIR}/utils_test/utils_test.c ${UTILS_TEST_SOURCES})

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