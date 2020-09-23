#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int strrev(char* s) {
    assert(s);

    size_t s_len = strlen(s);

    for (char *fore_p = s, *back_p = s + s_len - 1; fore_p < back_p; fore_p++, back_p--) {
        swap(char, *fore_p, *back_p);
    }

    int width = 1;
    for (char* back_p = s + s_len - 1; back_p >= s; back_p -= width) {
        width = char_width(*back_p);
        char* beg_p = back_p - (width - 1);
        if (width == ERROR_CHAR_NOT_VAL || width == ERROR_CHAR_NOT_BEG || beg_p < s) {
            return STR_REV_ERROR;
        }
        for (char* end_p = back_p; beg_p < end_p; beg_p++, end_p--) {
            swap(char, *beg_p, *end_p);
        }
    }

    return STR_REV_SUCCESS;
}

size_t strncnt(char const* str, size_t num, char const* cnt, size_t cnt_len) {
    assert(str);
    assert(cnt);

    if (!cnt_len) {
        return 0;
    }

    size_t num_cnt = 0;
    size_t i = 0;
    while (i <= (num - cnt_len) && str[i]) {
        if (strncmp(str + i, cnt, cnt_len) == 0) {
            num_cnt++;
            i += cnt_len;
        } else {
            i++;
        }
    }

    return num_cnt;
}

size_t strnrep_le(char* str, size_t num, char const* rep_from, size_t rep_from_len, char const* rep_with, size_t rep_with_len) {
    assert(str);
    assert(rep_from);
    assert(rep_from_len);
    assert(rep_with);
    assert(rep_with_len <= rep_from_len);

    size_t num_rep = 0,
           i = 0,
           r = 0;
    while (i < num && str[i]) {
        if (i <= (num - rep_from_len) && strncmp(str + i, rep_from, rep_from_len) == 0) {
            memcpy(str + r, rep_with, rep_with_len);
            i += rep_from_len;
            r += rep_with_len;
            num_rep++;
        } else {
            str[r++] = str[i++];
        }
    }

    assert(r <= i);

    memset(str + r, 0, i - r);

    return r;
}

size_t strnrep_g(char* str, size_t num, char const* rep_from, size_t rep_from_len, char const* rep_with, size_t rep_with_len) {
    assert(str);
    assert(rep_from);
    assert(rep_from_len);
    assert(rep_with);
    assert(rep_with_len > rep_from_len);

    char* tmp_str = calloc(num, sizeof(char));
    if (!tmp_str) {
        return 0;
    }

    size_t i = 0,
           r = 0;
    while (r < num - 1 && i < num && str[i]) {
        if (i <= (num - rep_from_len) && strncmp(str + i, rep_from, rep_from_len) == 0) {
            size_t num_copy = rep_with_len;
            if (r + num_copy >= num) {
                num_copy = num - r - 1;
            }
            memcpy(tmp_str + r, rep_with, num_copy);
            i += rep_from_len;
            r += num_copy;
        } else {
            tmp_str[r++] = str[i++];
        }
    }

    assert(r >= i);
    assert(tmp_str[num - 1] == '\0');

    strcpy(str, tmp_str);
    free(tmp_str);

    return r;
}

size_t strnrep(char* str, size_t num, char const* rep_from, size_t rep_from_len, char const* rep_with, size_t rep_with_len) {
    assert(str);
    assert(rep_from);
    assert(rep_with);

    if (!rep_from_len) {
        return 0;
    }
    if (rep_with_len <= rep_from_len) {
        return strnrep_le(str, num, rep_from, rep_from_len, rep_with, rep_with_len);
    }
    return strnrep_g(str, num, rep_from, rep_from_len, rep_with, rep_with_len);
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
