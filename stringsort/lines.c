#include "lines.h"

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
    char const** lines = malloc(sizeof(char const*) * lines_buffer_size);

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
    lines_s->lines = lines;
    lines_s->num_lines = num_read_lines;
    lines_s->_string_buffer = string_buffer;
    lines_s->_string_buffer_size = string_buffer_size;
    return lines_s;
}

void write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->num_lines; i++) {
        fprintf(file, "%s\n", lines->lines[i]);
    }
};

int is_good(char c) {
    return !(iscntrl(c) || isspace(c) || ispunct(c));
}

size_t find_alnum(const char* s, size_t i) {
    while (!(s[i] == '\0' || is_good(s[i]))) {
        i++;
    }
    return i;
}

int cmp(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    char const* left_string = *((char const* const*) left_value_p);
    char const* right_string = *((char const* const*) right_value_p);

    size_t li = find_alnum(left_string, 0),
           ri = find_alnum(right_string, 0);
    while (left_string[li] != '\0' &&
           right_string[ri] != '\0') {
        if (left_string[li] == right_string[ri]) {
            li = find_alnum(left_string, li + 1);
            ri = find_alnum(right_string, ri + 1);
            continue;
        }
        return (left_string[li] < right_string[ri]) ? -1 : 1;
    }

    if (left_string[li] == '\0' && right_string[ri] != '\0') {
        return 1;
    }
    if (left_string[li] != '\0' && right_string[ri] == '\0') {
        return -1;
    }
    return 0;
}

void sort_lines(LINES* lines) {
    assert(lines);

    qsort(lines->lines, lines->num_lines, sizeof(char*), &cmp);
}

void free_lines(LINES* lines) {
    assert(lines);

    free(lines->lines);
    free(lines->_string_buffer);
    lines->lines = NULL;
    lines->num_lines = 0;
    lines->_string_buffer = NULL;
    lines->_string_buffer_size = 0;
}
