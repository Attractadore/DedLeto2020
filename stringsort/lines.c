#include "lines.h"
#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>

// If our input doesn't end with a new line, append one
size_t sanitize_buffer(char** buffer_ptr, size_t buffer_size) {
    if ((*buffer_ptr)[buffer_size - 1] != '\n') {
        buffer_size++;
        char* new_buffer = realloc(*buffer_ptr, buffer_size);
        if (new_buffer) {
            return 0;
        }
        new_buffer[buffer_size - 1] = '\n';
    }
    return buffer_size;
}

LINES* read_lines(FILE* input_file) {
    assert(input_file);

    char* string_buffer = NULL;
    size_t string_buffer_size = read_buffer(input_file, &string_buffer);
    if (!string_buffer || !string_buffer_size) {
        return NULL;
    }

    string_buffer_size = sanitize_buffer(&string_buffer, string_buffer_size);
    if (!string_buffer_size) {
        free(string_buffer);
        return NULL;
    }

    assert(string_buffer);

    size_t lines_buffer_size = strncnt(string_buffer, string_buffer_size, "\n", 1);
    {
        size_t replace_sbuffer_size = strnrep(string_buffer, string_buffer_size, "\n", 1, "\0", 1);
        if (!replace_sbuffer_size) {
            free(string_buffer);
            return NULL;
        }
        assert(replace_sbuffer_size == string_buffer_size);
    }
    size_t num_read_lines = 0;
    char** lines = calloc(lines_buffer_size, sizeof(*lines));
    if (!lines) {
        free(string_buffer);
        return NULL;
    }

    char p = '\0';
    for (size_t i = 0; i < string_buffer_size; i++) {
        if (p == '\0') {
            lines[num_read_lines++] = string_buffer + i;
        }
        p = string_buffer[i];
    }

    assert(num_read_lines == lines_buffer_size);

    LINES* lines_s = calloc(1, sizeof(*lines_s));
    if (!lines_s) {
        free(lines);
        free(string_buffer);
        return NULL;
    }

    lines_s->_lines = lines;
    lines_s->_num_lines = num_read_lines;
    lines_s->_string_buffer = string_buffer;
    lines_s->_string_buffer_size = string_buffer_size;

    return lines_s;
}

int reverse_lines(LINES* lines) {
    assert(lines);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        if (strrev(lines->_lines[i]) != STR_REV_SUCCESS) {
            return REVERSE_LINES_ERROR;
        }
    }
    return REVERSE_LINES_SUCCESS;
}

int write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        if (fprintf(file, "%s\n", lines->_lines[i]) < 0) {
            return WRITE_LINES_ERROR;
        }
    }
    return WRITE_LINES_SUCCESS;
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
