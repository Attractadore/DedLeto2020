#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 8192
#define SWAP_BUFFER_SIZE (64)

void memswap(void* a, void* b, size_t num) {
    assert(a);
    assert(b);
    assert(b >= a + num || a >= b + num);

    static char swap_buffer[SWAP_BUFFER_SIZE];

    while (num) {
        size_t num_cp = SWAP_BUFFER_SIZE;
        if (num <= SWAP_BUFFER_SIZE) {
            num_cp = num;
        }
        memcpy(swap_buffer, a, num_cp);
        memcpy(a, b, num_cp);
        memcpy(b, swap_buffer, num_cp);
        num -= num_cp;
        a += num;
        b += num;
    }
}

size_t shrink_buffer(char** buffer_p, size_t old_buffer_size, size_t new_buffer_size) {
    if (old_buffer_size > new_buffer_size) {
        char* new_buffer = realloc(*buffer_p, new_buffer_size);
        if (new_buffer) {
            *buffer_p = new_buffer;
        }
        return new_buffer_size;
    }
    return old_buffer_size;
}

size_t read_buffer_stream(FILE* input_file, char** buffer_p) {
    assert(input_file);
    assert(buffer_p);

    *buffer_p = NULL;

    size_t buffer_size = DEFAULT_BUFFER_SIZE;
    char* buffer = calloc(buffer_size, sizeof(*buffer));
    if (!buffer) {
        return 0;
    }

    size_t num_read_chars = 0;
    char c = '\0';
    while ((c = fgetc(input_file)) != EOF) {
        if (num_read_chars == buffer_size) {
            size_t new_buffer_size = buffer_size * 2;
            char* new_buffer = realloc(buffer, new_buffer_size);
            if (!new_buffer) {
                break;
            }
            buffer_size = new_buffer_size;
            buffer = new_buffer;
        }
        buffer[num_read_chars++] = c;
    }

    if (!num_read_chars) {
        free(buffer);
        return 0;
    }

    assert(buffer_size >= num_read_chars);

    buffer_size = shrink_buffer(&buffer, buffer_size, num_read_chars);

    assert(buffer);

    *buffer_p = buffer;
    return buffer_size;
}

size_t read_buffer_file(FILE* input_file, char** buffer_p) {
    assert(input_file);
    assert(buffer_p);

    *buffer_p = NULL;

    fseek(input_file, 0, SEEK_END);
    long file_end = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    long file_beg = ftell(input_file);

    if (file_beg < 0 || file_end < 0 || file_end <= file_beg) {
        return 0;
    }

    size_t buffer_size = file_end - file_beg;
    char* buffer = calloc(buffer_size, sizeof(*buffer));
    if (!buffer) {
        return 0;
    }

    size_t read_buffer_size = fread(buffer, sizeof(char), buffer_size, input_file);
    if (!read_buffer_size) {
        free(buffer);
        return 0;
    }

    assert(buffer_size >= read_buffer_size);

    buffer_size = shrink_buffer(&buffer, buffer_size, read_buffer_size);

    assert(buffer);

    *buffer_p = buffer;
    return buffer_size;
}

bool is_stream(FILE* input_file) {
    return input_file == stdin;
}

size_t read_buffer(FILE* input_file, char** buf_p) {
    assert(input_file);
    assert(buf_p);

    size_t buffer_size = 0;
    if (is_stream(input_file)) {
        buffer_size = read_buffer_stream(input_file, buf_p);
    } else {
        buffer_size = read_buffer_file(input_file, buf_p);
    }

    return buffer_size;
}

bool is_sorted(void const* arr, size_t num, size_t sz, comparator comp) {
    assert(arr);
    assert(comp);

    for (void const* p = arr; p < arr + num * sz - sz; p += sz) {
        if (comp(p, p + sz) > 0) {
            return false;
        }
    }

    return true;
}

void* partition(void* arr, size_t num, size_t sz, comparator comp) {
    assert(arr);
    assert(comp);

    void* i = arr;
    void* pivot = arr + (num - 1) * sz;
    for (void* j = arr; j < pivot; j += sz) {
        if (comp(j, pivot) <= 0) {
            if (i != j) {
                memswap(i, j, sz);
            }
            i += sz;
        }
    }
    if (i != pivot) {
        memswap(i, pivot, sz);
    }
    return i;
}

void quick_sort(void* arr, size_t num, size_t sz, comparator comp) {
    assert(arr);
    assert(comp);

    if (is_sorted(arr, num, sz, comp)) {
        return;
    }

    void* mid = partition(arr, num, sz, comp);
    size_t mid_num = (mid - arr) / sz;

    quick_sort(arr, mid_num, sz, comp);
    quick_sort(mid + sz, num - mid_num - 1, sz, comp);
}
