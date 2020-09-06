#include "lines.h"
#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>

LINES* read_lines(FILE* input_file) {
    assert(input_file);

    char* string_buffer = NULL;
    size_t string_buffer_size = read_buffer(input_file, &string_buffer);

    size_t lines_buffer_size = 0;
    for (size_t i = 0; i < string_buffer_size; i++) {
        if (string_buffer[i] == '\n') {
            string_buffer[i] = '\0';
        }
        lines_buffer_size += (string_buffer[i] == '\0');
    }
    size_t num_read_lines = 0;
    char** lines = malloc(sizeof(*lines) * lines_buffer_size);

    char p = '\0';
    for (size_t i = 0; i < string_buffer_size; i++) {
        if (p == '\0') {
            lines[num_read_lines++] = string_buffer + i;
        }
        p = string_buffer[i];
    }

    LINES* lines_s = malloc(sizeof(*lines_s));
    lines_s->_lines = lines;
    lines_s->_num_lines = num_read_lines;
    lines_s->_string_buffer = string_buffer;
    lines_s->_string_buffer_size = string_buffer_size;

    return lines_s;
}

void reverse_lines(LINES* lines) {
    assert(lines);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        strrev(lines->_lines[i]);
    }
}

void write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        fprintf(file, "%s\n", lines->_lines[i]);
    }
}

int qsort_strcmp(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    char const* const* left_str_p = left_value_p;
    char const* const* right_str_p = right_value_p;
    return strcmp_alnum(*left_str_p, *right_str_p);
}

void sort_lines(LINES* lines) {
    assert(lines);

    qsort(lines->_lines, lines->_num_lines, sizeof(*(lines->_lines)), qsort_strcmp);
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
