#!/bin/bash

export CC_FLAGS="-std=c99 -Wall -Wextra -lcheck"

gcc $CC_FLAGS ../stringsort/test_file.c ../stringsort/file.c -o test_file
./test_file
