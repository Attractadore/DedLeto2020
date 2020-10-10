#include "string_helper.h"
#include "util.h"

#include <assert.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

size_t wstrcnt(wchar_t const* wstr, wchar_t wc) {
    assert(wstr);

    if (wc == L'\0') {
        return 0;
    }

    size_t cnt = 0;
    while ((wstr = wcschr(wstr, wc))) {
        wstr++;
        cnt++;
    }
    return cnt;
}

wchar_t const* find_alpha(wchar_t const* start, wchar_t const* end, ptrdiff_t step) {
    assert(start);
    assert(end);
    assert(step == 1 || step == -1);

    while (start != end && !iswalpha(*start)) {
        start += step;
    }
    return start;
}

int wstrcmp_common(wchar_t const* left_wstr_start, wchar_t const* left_wstr_end, wchar_t const* right_wstr_start, wchar_t const* right_wstr_end, ptrdiff_t step) {
    assert(left_wstr_start);
    assert(left_wstr_end);
    assert(right_wstr_start);
    assert(right_wstr_end);
    assert(step == 1 || step == -1);

    while ((left_wstr_start = find_alpha(left_wstr_start, left_wstr_end, step)) &&
           (right_wstr_start = find_alpha(right_wstr_start, right_wstr_end, step)) &&
           left_wstr_start != left_wstr_end &&
           right_wstr_start != right_wstr_end) {
        wchar_t lwc = towlower(*left_wstr_start);
        wchar_t rwc = towlower(*right_wstr_start);
        if (lwc != rwc) {
            return lwc - rwc;
        }
        left_wstr_start += step;
        right_wstr_start += step;
    }

    return (right_wstr_start == right_wstr_end) - (left_wstr_start == left_wstr_end);
}

int wstrcmp_alpha_fow(wide_string const* left_wide_string, wide_string const* right_wide_string) {
    assert(left_wide_string);
    assert(right_wide_string);
    assert(left_wide_string->str);
    assert(right_wide_string->str);

    wchar_t const* left_wstr_start = left_wide_string->str;
    wchar_t const* left_wstr_end = left_wide_string->str + left_wide_string->len;
    wchar_t const* right_wstr_start = right_wide_string->str;
    wchar_t const* right_wstr_end = right_wide_string->str + right_wide_string->len;

    return wstrcmp_common(left_wstr_start, left_wstr_end, right_wstr_start, right_wstr_end, 1);
}

int wstrcmp_alpha_rev(wide_string const* left_wide_string, wide_string const* right_wide_string) {
    assert(left_wide_string);
    assert(right_wide_string);
    assert(left_wide_string->str);
    assert(right_wide_string->str);

    wchar_t const* left_wstr_start = left_wide_string->str + left_wide_string->len - 1;
    wchar_t const* left_wstr_end = left_wide_string->str - 1;
    wchar_t const* right_wstr_start = right_wide_string->str + right_wide_string->len - 1;
    wchar_t const* right_wstr_end = right_wide_string->str - 1;

    return wstrcmp_common(left_wstr_start, left_wstr_end, right_wstr_start, right_wstr_end, -1);
}
