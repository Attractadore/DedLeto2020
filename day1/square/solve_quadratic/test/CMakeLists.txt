cmake_minimum_required(VERSION 3.18)

find_package(check REQUIRED)

project("test_solve_quadratic")
add_executable(${PROJECT_NAME} "test_solve_quadratic.c")
target_link_libraries(${PROJECT_NAME} solve_quadratic check)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
