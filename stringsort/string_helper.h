/**
 * \file string_helper.h This file defines helper function for working with strings and characters
 */
#pragma once
#include <stddef.h>

/**
 * \brief This function reverses a wide string in-place
 *
 * \param[in, out] wstr The wide string that will be reversed
 */
void wstrrev(wchar_t* wstr);

/**
 * \brief This function counts how many times a wide character occurs in a wide string
 *
 * \param[in] wstr The wide string in which to count a wide character's occurances
 * \param[in] wc The wide character whose number of occurances to count
 *
 * \return The number of occurances of \c wc in \c wstr
 */
size_t wstrcnt(wchar_t const* wstr, wchar_t wc);

/**
 * \brief This function replaces all occurances of one wide character in a wide string with another
 *
 * \param[in, out] wstr The wide string this function will operate on
 * \param[in] fwc The wide character to replace
 * \param[in] twc The wide character to replace with
 *
 * \return The number of replacements made
 */
size_t wstrrep(wchar_t* wstr, wchar_t fwc, wchar_t twc);

/**
 * \brief This function compares two wide strings ignoring non-alnum wide characters
 *
 * \param[in] left_wstr, right_wstr The wide strings this function will compare
 *
  \return < 0 if left_wstr < right_wstr, 0 if left_wstr == right_wstr, > 0 if left_wstr > right_wstr
 *
 * \remark This function considers an empty wide string to be greater than any other wide string,
 *         and a prefix wide string to be greater than any wide string it is a prefix of
 */
int wstrcmp_alnum(wchar_t const* left_wstr, wchar_t const* right_wstr);
