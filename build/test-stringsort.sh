#!/bin/bash

CC_FLAGS="-std=c99 -Wall -Wextra -lcheck"

gcc $CC_FLAGS ../stringsort/test_file.c ../stringsort/file.c -o test_file
gcc $CC_FLAGS ../stringsort/test_string_helper.c ../stringsort/string_helper.c -o test_string_helper
gcc $CC_FLAGS ../stringsort/test_util.c ../stringsort/util.c -o test_util
./test_file
./test_string_helper
./test_util
