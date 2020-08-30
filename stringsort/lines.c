#include "lines.h"

#include <assert.h>
#include <stdlib.h>

#define DEFAULT_NUM_LINES 8192
#define DEFAULT_NUM_CHARS 128

void free_lines(char** lines, size_t num_lines) {
    assert(lines);

    for (size_t i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}

size_t read_lines(FILE* input_stream, char*** lines_p) {
    assert(lines_p);

    size_t num_read_lines = 0,
           lines_buffer_size = DEFAULT_NUM_LINES;
    char** lines = malloc(sizeof(char*) * lines_buffer_size);

    char c = '\0',
         p = '\0';
    size_t num_read_chars = 0,
           current_line_buffer_size = 0;
    char* current_line = NULL;
    while ((c = fgetc(input_stream)) != EOF) {
        if (c == '\n') {
            c = '\0';
        }
        if (p == '\0') {
            num_read_chars = 0;
            current_line_buffer_size = DEFAULT_NUM_CHARS;
            current_line = malloc(sizeof(char) * current_line_buffer_size);
            if (num_read_lines == lines_buffer_size) {
                lines_buffer_size *= 2;
                lines = realloc(lines, lines_buffer_size);
            }
            lines[num_read_lines++] = current_line;
        }
        if (num_read_chars == current_line_buffer_size) {
            current_line_buffer_size *= 2;
            current_line = realloc(current_line, current_line_buffer_size);
        }
        current_line[num_read_chars++] = c;
        p = c;
    }

    *lines_p = lines;
    return num_read_lines;
}
