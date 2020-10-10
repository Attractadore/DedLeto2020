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
 * \return The number of occurances of \c wc in \c wstr, \c 0 if \c wc is \c '\0'
 */
size_t wstrcnt(wchar_t const* wstr, wchar_t wc);

typedef struct {
    wchar_t const* str;
    size_t len;
} wide_string;

/**
 * \brief This function compares two wide strings left to right ignoring non-alpha wide characters
 *
 * \param[in] left_wide_string, right_wide_string The wide strings this function will compare
 *
 * \return < 0 if left_wstr < right_wstr, 0 if left_wstr == right_wstr, > 0 if left_wstr > right_wstr
 */
int wstrcmp_alpha_fow(wide_string const* left_wide_string, wide_string const* right_wide_string);

/**
 * \brief This function compares two wide strings left to right ignoring non-alpha wide characters
 *
 * \param[in] left_wide_string, right_wide_string The wide strings this function will compare
 *
 * \return < 0 if left_wstr < right_wstr, 0 if left_wstr == right_wstr, > 0 if left_wstr > right_wstr
 */
int wstrcmp_alpha_rev(wide_string const* left_wide_string, wide_string const* right_wide_string);
