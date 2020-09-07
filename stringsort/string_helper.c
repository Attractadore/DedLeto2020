#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>

int strrev(char* s) {
    assert(s);

    size_t s_len = strlen(s);
    if (!s_len) {
        return STR_REV_SUCCESS;
    }

    for (size_t i = 0, j = s_len - 1; i < j; i++, j--) {
        swap(char, s[i], s[j]);
    }

    int width = 1;
    for (long int i = s_len - 1; i >= 0; i -= width) {
        width = char_width(s[i]);
        long int symbol_beg = i - (width - 1);
        if (width == ERROR_CHAR_NOT_VAL || width == ERROR_CHAR_NOT_BEG || symbol_beg < 0) {
            return STR_REV_ERROR;
        }
        for (size_t j = symbol_beg, k = i; j < k; j++, k--) {
            swap(char, s[j], s[k]);
        }
    }

    return STR_REV_SUCCESS;
}

int char_width(char c) {
    unsigned char uc = c;  // Left shifting negative signed chars produces 1's
    if (uc >> 7 == 0b0) {  // utf-8 1 byte symbols begin with 0xxxxxxx
        return 1;
    }
    if (uc >> 6 == 0b10) {  // utf-8 multibyte symbols are continued with 10xxxxxx
        return ERROR_CHAR_NOT_BEG;
    }
    if (uc >> 5 == 0b110) {  // utf-8 2 byte symbols begin with 110xxxxx
        return 2;
    }
    if (uc >> 4 == 0b1110) {  // utf-8 3 byte symbols begin with 1110xxxx
        return 3;
    }
    if (uc >> 3 == 0b11110) {  // utf-8 4 byte symbols begin with 11110xxx
        return 4;
    }
    return ERROR_CHAR_NOT_VAL;
}

int is_alnum(char c) {
    return !(iscntrl(c) || isspace(c) || ispunct(c));
}

char const* find_alnum(char const* s) {
    assert(s);

    while (*s && !is_alnum(*s)) {
        s++;
    }
    return s;
}

int strcmp_alnum(char const* left_str, char const* right_str) {
    assert(left_str);
    assert(right_str);

    left_str = find_alnum(left_str);
    right_str = find_alnum(right_str);
    while (*left_str && *right_str) {
        if (*left_str != *right_str) {
            return *left_str - *right_str;
        }
        left_str = find_alnum(left_str + 1);
        right_str = find_alnum(right_str + 1);
    }

    if (!*left_str && *right_str) {
        return 1;
    }
    if (*left_str && !*right_str) {
        return -1;
    }
    return 0;
}
