#include "util.h"

#include <assert.h>
#include <stdlib.h>

#define DEFAULT_BUFFER_SIZE 8192

size_t read_buffer(FILE* input_file, char** buf_p) {
    assert(input_file);
    assert(buf_p);

    size_t buffer_size = 0;
    char* buffer = NULL;
    if (input_file == stdin) {
        buffer_size = DEFAULT_BUFFER_SIZE;
        buffer = malloc(buffer_size);
        size_t num_read_chars = 0;
        char c = '\0';
        while ((c = getchar()) != EOF) {
            if (num_read_chars == buffer_size) {
                buffer_size *= 2;
                buffer = realloc(buffer, buffer_size);
            }
            buffer[num_read_chars++] = c;
        }
        buffer_size = num_read_chars;
        buffer = realloc(buffer, buffer_size);
    } else {
        fseek(input_file, 0, SEEK_END);
        long file_end = ftell(input_file);
        fseek(input_file, 0, SEEK_SET);
        long file_beg = ftell(input_file);
        if (file_end >= 0 && file_beg >= 0) {
            buffer_size = file_end - file_beg;
            buffer = malloc(buffer_size);
            fread(buffer, sizeof(char), buffer_size, input_file);
        }
    }

    *buf_p = buffer;
    return buffer_size;
}
