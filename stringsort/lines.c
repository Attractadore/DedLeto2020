#include "lines.h"
#include "string_helper.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUM_LINES 8192
#define DEFAULT_BUFFER_SIZE 8192

LINES* read_lines(FILE* input_file) {
    assert(input_file);

    size_t num_read_lines = 0,
           lines_buffer_size = DEFAULT_NUM_LINES;
    char** lines = malloc(sizeof(char const*) * lines_buffer_size);

    size_t string_buffer_size = 0;
    char* string_buffer = NULL;
    if (input_file == stdin) {
        string_buffer_size = DEFAULT_BUFFER_SIZE;
        string_buffer = malloc(string_buffer_size);
        size_t num_read_chars = 0;
        char c = '\0';
        while ((c = getchar()) != EOF) {
            if (num_read_chars == string_buffer_size) {
                string_buffer_size *= 2;
                string_buffer = realloc(string_buffer, string_buffer_size);
            }
            string_buffer[num_read_chars++] = c;
        }
        string_buffer_size = num_read_chars;
        string_buffer = realloc(string_buffer, string_buffer_size);
    } else {
        fseek(input_file, 0, SEEK_SET);
        long file_beg = ftell(input_file);
        fseek(input_file, 0, SEEK_END);
        long file_end = ftell(input_file);
        fseek(input_file, 0, SEEK_SET);
        string_buffer_size = file_end - file_beg;
        string_buffer = malloc(string_buffer_size);
        fread(string_buffer, 1, string_buffer_size, input_file);
    }

    char p = '\0';
    for (size_t i = 0; i < string_buffer_size; i++) {
        if (p == '\0') {
            if (num_read_lines == lines_buffer_size) {
                lines_buffer_size *= 2;
                lines = realloc(lines, lines_buffer_size);
            }
            lines[num_read_lines++] = string_buffer + i;
        }

        if (string_buffer[i] == '\n') {
            string_buffer[i] = '\0';
        }

        p = string_buffer[i];
    }

    LINES* lines_s = malloc(sizeof(LINES));
    lines_s->_lines = lines;
    lines_s->_num_lines = num_read_lines;
    lines_s->_string_buffer = string_buffer;
    lines_s->_string_buffer_size = string_buffer_size;
    return lines_s;
}

void reverse_lines(LINES* lines) {
    for (size_t i = 0; i < lines->_num_lines; i++) {
        string_reverse(lines->_lines[i]);
    }
}

void write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        fprintf(file, "%s\n", lines->_lines[i]);
    }
};

void sort_lines(LINES* lines) {
    assert(lines);

    qsort(lines->_lines, lines->_num_lines, sizeof(char*), &cmp_str);
}

void free_lines(LINES* lines) {
    assert(lines);

    free(lines->_lines);
    free(lines->_string_buffer);
    lines->_lines = NULL;
    lines->_num_lines = 0;
    lines->_string_buffer = NULL;
    lines->_string_buffer_size = 0;
}
