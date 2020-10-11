#include "lines.h"
#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

typedef enum write_lines_error_enum {
    WRITE_OK,
    WRITE_ERROR,
} WRITE_LINES_ERROR;

typedef struct _lines_s {
    wide_string** _lines;
    wide_string* _lines_buffer;
    size_t _num_lines;
    wchar_t* _string_buffer;
    size_t _string_buffer_size;
} LINES;

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

    // POSIX extension
    size_t wbuffer_size = mbstowcs(NULL, sbuffer, 0) + 1;
    wchar_t* wbuffer = calloc(wbuffer_size, sizeof(*wbuffer));
    *wbuffer_p = wbuffer;
    if (!wbuffer) {
        return 0;
    }
    mbstowcs(wbuffer, sbuffer, wbuffer_size);
    return wbuffer_size;
}

size_t assign_lines(wide_string*** lines_p, wide_string** lines_buffer_p, wchar_t* wbuffer, size_t wbuffer_size) {
    assert(lines_p);
    assert(wbuffer);

    size_t lines_buffer_size = wstrcnt(wbuffer, L'\n') + 1;

    wide_string* lines_buffer = calloc(lines_buffer_size, sizeof(*lines_buffer));
    *lines_buffer_p = lines_buffer;
    if (!lines_buffer) {
        return 0;
    }

    wide_string** lines = calloc(lines_buffer_size, sizeof(*lines));
    *lines_p = lines;
    if (!lines) {
        *lines_buffer_p = NULL;
        free(lines_buffer);
        return 0;
    }

    size_t num_read_lines = 0;
    wchar_t p = L'\n';
    for (size_t i = 0; i < wbuffer_size; i++) {
        if (p == L'\n') {
            lines_buffer[num_read_lines].str = wbuffer + i;
            lines[num_read_lines] = lines_buffer + num_read_lines;
            num_read_lines++;
        } else {
            lines_buffer[num_read_lines - 1].len++;
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

    wide_string** lines = NULL;
    wide_string* lines_buffer = NULL;
    size_t num_read_lines = assign_lines(&lines, &lines_buffer, wbuffer, wbuffer_size);
    if (!lines_buffer || !lines) {
        free(wbuffer);
        return NULL;
    }

    wbuffer[wbuffer_size - 1] = L'\n';

    LINES* lines_s = calloc(1, sizeof(*lines_s));
    if (!lines_s) {
        free(lines);
        free(wbuffer);
        return NULL;
    }

    lines_s->_string_buffer = wbuffer;
    lines_s->_string_buffer_size = wbuffer_size;
    lines_s->_lines = lines;
    lines_s->_lines_buffer = lines_buffer;
    lines_s->_num_lines = num_read_lines;

    return lines_s;
}

WRITE_LINES_ERROR write_lines(const LINES* lines, FILE* file) {
    assert(lines);
    assert(file);

    for (size_t i = 0; i < lines->_num_lines; i++) {
        if (fwprintf(file, L"%.*ls\n", lines->_lines[i]->len, lines->_lines[i]->str) < 0) {
            return WRITE_ERROR;
        }
    }
    return WRITE_OK;
}

int qsort_cmp_forward(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    wide_string const* const* left_wide_string_p = left_value_p;
    wide_string const* const* right_wide_string_p = right_value_p;

    return wstrcmp_alpha_fow(*left_wide_string_p, *right_wide_string_p);
}

int qsort_cmp_reverse(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    wide_string const* const* left_wide_string_p = left_value_p;
    wide_string const* const* right_wide_string_p = right_value_p;

    return wstrcmp_alpha_rev(*left_wide_string_p, *right_wide_string_p);
}

void sort_lines(LINES* lines, sorter sort, comparator comp) {
    assert(lines);
    assert(lines->_lines);
    assert(sort);
    assert(comp);

    sort(lines->_lines, lines->_num_lines, sizeof(*(lines->_lines)), comp);
}

void free_lines(LINES* lines) {
    if (lines) {
        free(lines->_lines);
        free(lines->_string_buffer);
        free(lines);
    }
}

STRINGSORT_ERROR stringsort(FILE* input_file, FILE* output_file) {
    assert(input_file);
    assert(output_file);

    setlocale(LC_ALL, "");
    LINES* lines = read_lines(input_file);
    if (!lines) {
        return SORT_READ_ERROR;
    }

    sort_lines(lines, quick_sort, qsort_cmp_forward);
    if (write_lines(lines, output_file) != WRITE_OK || fwprintf(output_file, L"\n") < 0) {
        free_lines(lines);
        return SORT_WRITE_ERROR;
    }

    sort_lines(lines, qsort, qsort_cmp_reverse);
    if (write_lines(lines, output_file) != WRITE_OK || fwprintf(output_file, L"\n") < 0) {
        free_lines(lines);
        return SORT_WRITE_ERROR;
    }

    size_t num_chars = lines->_string_buffer_size;
    wchar_t const* write_p = lines->_string_buffer;
    while (num_chars) {
        int num_write = (num_chars < INT_MAX) ? num_chars : INT_MAX;
        if (fwprintf(output_file, L"%.*ls", num_write, write_p) < 0) {
            free_lines(lines);
            return SORT_WRITE_ERROR;
        }
        write_p += num_write;
        num_chars -= num_write;
    }

    free_lines(lines);

    return SORT_OK;
}

char const* get_stringsort_error(STRINGSORT_ERROR err) {
    switch (err) {
        case SORT_OK:
            return "No error";
        case SORT_READ_ERROR:
            return "Error while trying to read from input file";
        case SORT_WRITE_ERROR:
            return "Error while trying to write to output file";
        case SORT_EXEC_ERROR:
            return "Execution error";
        default:
            return "Unknow error";
    }
}
