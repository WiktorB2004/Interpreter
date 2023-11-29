## EXAMPLE ##
# Set the test sources
# set(TEST_SOURCES
#     test_file1.c
#     test_file2.c
# )

# Add an executable for tests
# add_executable(test_executable ${TEST_SOURCES})

# Link test executable with the project library or source files
# target_link_libraries(test_executable PRIVATE library_name) 

# Add tests
# add_test(NAME my_tests COMMAND test_executable)

# Optionally, set output directories for test files
# set_target_properties(test_executable PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
#     ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj
# )
