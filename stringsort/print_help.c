#include "print_help.h"

#include <stdio.h>

void print_help(char const* program_name) {
    printf("This program sorts an input file's lines and stores the result in an output file\n"
           "To use this program, run %s [input file name] [output file name]\n"
           "If you want to read from stdin, [input file name] should be \"stdin\"\n"
           "If you want to write to stdout, [output file name] should be \"stdout\"\n",
           program_name);
}
