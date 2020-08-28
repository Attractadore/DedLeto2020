cmake_minimum_required(VERSION 3.18)

find_package(check REQUIRED)

project("test_is_equal")
add_executable(${PROJECT_NAME} "test_is_equal.c")
target_link_libraries(${PROJECT_NAME} is_equal check)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
