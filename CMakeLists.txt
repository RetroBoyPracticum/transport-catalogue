cmake_minimum_required(VERSION 3.20)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

file(GLOB SOURCE "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}
)

add_library(${PROJECT_NAME}_lib ${SOURCE})

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

# Add tests subdirectory
add_subdirectory(tests)