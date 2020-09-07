#!/bin/bash

gcc -std=c99 -g -Og -Wall -Wextra ../stringsort/lines.c ../stringsort/encyclopedia_sort.c ../stringsort/file.c ../stringsort/string_helper.c ../stringsort/program.c ../stringsort/util.c -o encyclopedia_sort
gcc -std=c99 -g -Og -Wall -Wextra ../stringsort/lines.c ../stringsort/rhyme_sort.c ../stringsort/file.c ../stringsort/string_helper.c ../stringsort/program.c ../stringsort/util.c -o rhyme_sort
