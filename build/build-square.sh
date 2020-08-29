#!/bin/bash

gcc -std=c99 -Wall -Wextra ../square/is_equal.c ../square/solve_quadratic.c ../square/main.c -o square -lm
