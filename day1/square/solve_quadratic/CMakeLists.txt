cmake_minimum_required(VERSION 3.18)

project("solve_quadratic")
add_library(${PROJECT_NAME} "src/solve_quadratic.c")
target_include_directories(${PROJECT_NAME} PUBLIC "include/")
target_link_libraries(${PROJECT_NAME} is_equal m)

if(BUILD_TESTING)
    add_subdirectory("test/")
endif()
