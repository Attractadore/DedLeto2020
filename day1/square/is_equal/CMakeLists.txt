cmake_minimum_required(VERSION 3.18)

project("is_equal")
add_library(${PROJECT_NAME} "src/is_equal.c")
target_include_directories(${PROJECT_NAME} PUBLIC "include/")

if(BUILD_TESTING)
    add_subdirectory("test/")
endif()
