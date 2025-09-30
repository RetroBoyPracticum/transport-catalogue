cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

enable_testing()

# Create test executable
file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME}_tests
    ${TEST_SOURCES}
)

# Link with the main project library and GTest
target_link_libraries(${PROJECT_NAME}_tests
    ${PROJECT_NAME}_lib
    gtest
)

target_include_directories(${PROJECT_NAME}_tests
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Add test to CTest
add_test(
    NAME ${PROJECT_NAME}_Tests
    COMMAND ${PROJECT_NAME}_tests
)

set_tests_properties(${PROJECT_NAME}_Tests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
