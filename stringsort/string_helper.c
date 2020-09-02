#include "string_helper.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h>

#define swap(t, a, b) \
    t tmp = a;        \
    a = b;            \
    b = tmp;

int string_reverse(char* s) {
    assert(s);

    size_t s_len = strlen(s);
    for (size_t i = 0; i < s_len / 2; i++) {
        swap(char, s[i], s[s_len - i - 1])
    }
    int w = 1;
    for (int i = s_len - 1; i >= 0; i -= w) {
        w = char_width(s[i]);
        if (w == ERROR_CHAR_NOT_VAL || w == ERROR_CHAR_NOT_BEG || i < (w - 1)) {
            return STR_REV_ERROR;
        }
        for (int j = i - (w - 1); j < i - (w - 1) / 2; j++) {
            swap(char, s[j], s[i - (j - i + (w - 1))]);
        }
    }
    return STR_REV_SUCCESS;
}

int char_width(char c) {
    if ((~(1 << 7) & c) == c) {  // utf-8 1 byte symbols begin with 0xxxxxxx
        return 1;
    }
    if ((~(1 << 6) & c) == c) {  // utf-8 multibyte symbols are continued with 10xxxxxx
        return ERROR_CHAR_NOT_BEG;
    }
    if ((~(1 << 5) & c) == c) {  // utf-8 2 byte symbols begin with 110xxxxx
        return 2;
    }
    if ((~(1 << 4) & c) == c) {  // utf-8 3 byte symbols begin with 1110xxxx
        return 3;
    }
    if ((~(1 << 3) & c) == c) {  // utf-8 4 byte symbols begin with 11110xxx
        return 4;
    }
    return ERROR_CHAR_NOT_VAL;
}

int is_good(char c) {
    return !(iscntrl(c) || isspace(c) || ispunct(c));
}

size_t find_good(char const* s, size_t i) {
    while (!(s[i] == '\0' || is_good(s[i]))) {
        i++;
    }
    return i;
}

int cmp_str(void const* left_value_p, void const* right_value_p) {
    assert(left_value_p);
    assert(right_value_p);

    char const* left_string = *((char const* const*) left_value_p);
    char const* right_string = *((char const* const*) right_value_p);

    size_t li = find_good(left_string, 0),
           ri = find_good(right_string, 0);
    while (left_string[li] != '\0' &&
           right_string[ri] != '\0') {
        if (left_string[li] == right_string[ri]) {
            li = find_good(left_string, li + 1);
            ri = find_good(right_string, ri + 1);
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
