#include "file.h"

#include <assert.h>
#include <string.h>

int valid_stdin_mode(char const* mode) {
    return strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0;
}

int valid_stdout_stderr_mode(char const* mode) {
    return strcmp(mode, "w") == 0 || strcmp(mode, "wb") == 0 ||
           strcmp(mode, "a") == 0 || strcmp(mode, "ab") == 0;
}

FILE* open_file(const char* file_name, const char* mode) {
    assert(file_name);
    assert(mode);

    if (strcmp(file_name, "stdin") == 0) {
        if (valid_stdin_mode(mode)) {
            return stdin;
        }
        return NULL;
    }
    if (strcmp(file_name, "stdout") == 0) {
        if (valid_stdout_stderr_mode(mode)) {
            return stdout;
        }
        return NULL;
    }
    if (strcmp(file_name, "stderr") == 0) {
        if (valid_stdout_stderr_mode(mode)) {
            return stderr;
        }
        return NULL;
    }
    return fopen(file_name, mode);
}

int close_file(FILE* file) {
    assert(file);

    if (file == stdin || file == stdout || file == stderr) {
        return EOF;
    }

    return fclose(file);
}
