#!/bin/bash

gcc -std=c99 -Wall -Wextra ../stringsort/lines.c ../stringsort/encyclopedia_sort.c ../stringsort/file.c ../stringsort/string_helper.c ../stringsort/print_help.c -o encyclopedia_sort
gcc -std=c99 -Wall -Wextra ../stringsort/lines.c ../stringsort/rhyme_sort.c ../stringsort/file.c ../stringsort/string_helper.c ../stringsort/print_help.c -o rhyme_sort
