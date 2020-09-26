#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

void wstrrev(wchar_t* wstr) {
    assert(wstr);

    for (wchar_t *fore_p = wstr, *back_p = wcschr(wstr, L'\0') - 1;
         fore_p < back_p;
         fore_p++, back_p--) {
        swap(wchar_t, *fore_p, *back_p);
    }
}

size_t wstrcnt(wchar_t const* wstr, wchar_t wc) {
    assert(wstr);
    assert(wc);

    size_t cnt = 0;
    while ((wstr = wcschr(wstr, wc))) {
        wstr++;
        cnt++;
    }
    return cnt;
}

size_t wstrrep(wchar_t* wstr, wchar_t fwc, wchar_t twc) {
    assert(wstr);
    assert(fwc);

    size_t rep = 0;
    while ((wstr = wcschr(wstr, fwc))) {
        *(wstr++) = twc;
        rep++;
    }
    return rep;
}

wchar_t const* find_alpha(wchar_t const* wstr) {
    assert(wstr);

    while (*wstr && !iswalpha(*wstr)) {
        wstr++;
    }
    return wstr;
}

int wstrcmp_alpha(wchar_t const* left_wstr, wchar_t const* right_wstr) {
    assert(left_wstr);
    assert(right_wstr);

    while ((left_wstr = find_alpha(left_wstr)) &&
           (right_wstr = find_alpha(right_wstr)) &&
           *left_wstr && *right_wstr) {
        wchar_t lwc = towlower(*(left_wstr++));
        wchar_t rwc = towlower(*(right_wstr++));
        if (lwc != rwc) {
            return lwc - rwc;
        }
    }

    if (!*left_wstr && *right_wstr) {
        return 1;
    }
    if (*left_wstr && !*right_wstr) {
        return -1;
    }
    return 0;
}
