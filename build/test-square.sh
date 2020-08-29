#!/bin/bash

echo "Compile test_is_equal"
gcc -std=c99 ../square/is_equal.c ../square/test_is_equal.c -o test_is_equal -lcheck
echo "Compile test_solve_quadratic"
gcc -std=c99 ../square/is_equal.c ../square/solve_quadratic.c ../square/test_solve_quadratic.c -o test_solve_quadratic -lm -lcheck

./test_is_equal
./test_solve_quadratic
