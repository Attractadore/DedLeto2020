#include "lines.h"
#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <wchar.h>

// If our input doesn't end with a new line, append one
size_t sanitize_buffer(char** buffer_p, size_t buffer_size) {
    assert(buffer_p);

    if (!buffer_size || (*buffer_p)[buffer_size - 1] != '\n') {
        buffer_size++;
        char* new_buffer = realloc(*buffer_p, buffer_size);
        if (!new_buffer) {
            return 0;
        }
        new_buffer[buffer_size - 1] = '\n';
        *buffer_p = new_buffer;
    }
    return buffer_size;
}

size_t convert_buffer(wchar_t** wbuffer_p, char const* sbuffer) {
    assert(wbuffer_p);
    assert(sbuffer);

    size_t wbuffer_size = mbstowcs(NULL, sbuffer, 0) + 1;
    wchar_t* wbuffer = calloc(wbuffer_size, sizeof(*wbuffer));
    *wbuffer_p = wbuffer;
    if (!wbuffer) {
        return 0;
    }
    mbstowcs(wbuffer, sbuffer, wbuffer_size);
    return wbuffer_size;
}

size_t assign_lines(wchar_t*** lines_p, wchar_t* wbuffer, size_t wbuffer_size) {
    assert(lines_p);
    assert(wbuffer);

    size_t lines_buffer_size = wstrcnt(wbuffer, L'\n') + 1;
    wchar_t** lines = calloc(lines_buffer_size, sizeof(*lines));
    *lines_p = lines;
    if (!lines) {
        return 0;
    }

    size_t num_read_lines = 0;
    wchar_t p = L'\n';
    for (size_t i = 0; i < wbuffer_size; i++) {
        if (p == L'\n') {
            lines[num_read_lines++] = wbuffer + i;
        }
        p = wbuffer[i];
    }

    assert(num_read_lines == lines_buffer_size);

    return num_read_lines;
}

LINES* read_lines(FILE* input_file) {
    assert(input_file);

    char* sbuffer = NULL;
    size_t sbuffer_size = read_buffer(input_file, &sbuffer);
    if (!sbuffer) {
        return NULL;
    }

    sbuffer_size = sanitize_buffer(&sbuffer, sbuffer_size);
    if (!sbuffer_size) {
        free(sbuffer);
        return NULL;
    }

    sbuffer[sbuffer_size - 1] = '\0';
    wchar_t* wbuffer = NULL;
    size_t wbuffer_size = convert_buffer(&wbuffer, sbuffer);
    free(sbuffer);
    if (!wbuffer) {
        return NULL;
    }

    wchar_t** lines = NULL;
    size_t num_read_lines = assign_lines(&lines, wbuffer, wbuffer_size);
    if (!lines) {
        free(wbuffer);
        return NULL;
    }

    size_t num_rep = wstrrep(wbuffer, L'\n', L'\0');
    assert(num_rep + 1 == num_read_lines);

    LINES* lines_s = calloc(1, sizeof(*lines_s));
    if (!lines_s) {
        free(lines);
        free(wbuffer);
        return NULL;
    }

    lines_s->_string_buffer = wbuffer;
    lines_s->_string_buffer_size = wbuffer_size;
    lines_s->_lines = lines;
    lines_s->_num_lines = num_read_lines;

    return lines_s;
}

void reverse_lines(LINES* lines) {
    assert(lines);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        wstrrev(lines->_lines[i]);
    }
}

int write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        if (fwprintf(file, L"%ls\n", lines->_lines[i]) < 0) {
            return WRITE_LINES_ERROR;
        }
    }
    return WRITE_LINES_SUCCESS;
}

int qsort_wstrcmp(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    wchar_t const* const* left_str_p = left_value_p;
    wchar_t const* const* right_str_p = right_value_p;
    return wstrcmp_alpha(*left_str_p, *right_str_p);
}

void sort_lines(LINES* lines) {
    assert(lines);

    qsort(lines->_lines, lines->_num_lines, sizeof(*(lines->_lines)), qsort_wstrcmp);
}

void free_lines(LINES* lines) {
    assert(lines);

    free(lines->_lines);
    free(lines->_string_buffer);
    free(lines);
}
