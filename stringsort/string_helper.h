/**
 * \file string_helper.h This file defines helper function for working with strings and characters
 */
#pragma once
#include <stddef.h>

/**
 * \brief This function counts how many times a wide character occurs in a wide string
 *
 * \param[in] wstr The wide string in which to count a wide character's occurances
 * \param[in] wc The wide character whose number of occurances to count
 *
 * \return The number of occurances of \c wc in \c wstr
 *
 * \remark \c wc must not be \c '\0'
 */
size_t wstrcnt(wchar_t const* wstr, wchar_t wc);

typedef struct {
    wchar_t const* str;
    size_t len;
} wide_string;

/**
 * \brief This function compares two wide strings ignoring non-alnum wide characters
 *
 * \param[in] left_wstr, right_wstr The wide strings this function will compare
 * \param[in] step The direction in which to compare the wide strings
 *
 * \return < 0 if left_wstr < right_wstr, 0 if left_wstr == right_wstr, > 0 if left_wstr > right_wstr
 *
 * \remark This function considers an empty wide string to be greater than any other wide string,
 *         and a prefix wide string to be greater than any wide string it is a prefix of;
 *         If \c step is > 0, comparison is done left to right, if \c step is < 0, comparison is done
 *         right to left, if \c step is 0, than the strings are considered equal 
 */
int wstrcmp_alpha(wide_string const* left_wide_string, wide_string const* right_wide_string, ptrdiff_t step);
