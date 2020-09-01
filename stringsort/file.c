#include "file.h"

#include <assert.h>
#include <string.h>

FILE* open_file(const char* file_name, const char* mode) {
    assert(file_name);
    assert(mode);

    if (strcmp(file_name, "stdin") == 0) {
        return stdin;
    }
    if (strcmp(file_name, "stdout") == 0) {
        return stdout;
    }
    return fopen(file_name, mode);
}

int close_file(FILE* file) {
    assert(file);

    if (file != stdin && file != stdout) {
        return fclose(file);
    }
    return 0;
}
