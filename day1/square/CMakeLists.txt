cmake_minimum_required(VERSION 3.18)

project("square")

include(CTest)

add_subdirectory("is_equal/")
add_subdirectory("solve_quadratic/")

add_executable(${PROJECT_NAME} "src/main.c")
target_link_libraries(${PROJECT_NAME} solve_quadratic)
