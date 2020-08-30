#include "sort.h"

#include <stdlib.h>
#include <string.h>

int cmp(void const* lhs, void const* rhs) {
    char const* const* slhs = lhs;
    char const* const* srhs = rhs;
    return strcmp(*slhs, *srhs);
}

void sort_lines(char** lines, size_t num_lines) {
    qsort(lines, num_lines, sizeof(char*), &cmp);
}
