/**
 * \file string_helper.h This file defines helper function for working with strings and characters
 */
#pragma once
#include <stddef.h>

/** This symbolic parameter is used to indicate that a string was successfully reversed */
#define STR_REV_SUCCESS 0
/** This symbolic parameter is used to indicate that an error occured while trying to reverse a string */
#define STR_REV_ERROR -1

/** This symbolic paramater is used to indicate that a utf-8 symbol cannot begin with a given byte */
#define ERROR_CHAR_NOT_BEG 0
/** This symbolic paramater is used to indicate that a given byte is not valid utf-8 */
#define ERROR_CHAR_NOT_VAL -1

/**
 * \brief This function reverses a utf-8 string in-place
 *
 * \param[in, out] s The string that will be reversed
 * 
 * \return #STR_REV_SUCCESS if reversed string, #STR_REV_ERROR otherwise
 */
int strrev(char* s);

/**
 * \brief This function counts how many times a substring occurs in a string
 *
 * \param[in] str The string in which to count a substring's occurances
 * \param[in] num The maximum number of characters in \c str to process
 * \param[in] cnt The substring whose number of occurances to count
 * \param[in] cnt_len The length of the substring to search for
 *
 * \return The number of occurances of \c cnt in \c str
 *
 * \remark This function counts occurances of \c cnt in \c str either until has encountered \c '\0' or it has processed \c num chars;
 *         \c cnt_len is not required to be null-terminated;
 *         This function counts non-overlapping substrings;
 */
size_t strncnt(char const* str, size_t num, char const* cnt, size_t cnt_len);

/**
 * \brief This function replaces all occurances of one substring in a string with another substring
 *
 * \param[in, out] str The string this function will operate on
 * \param[in] num The maximum number of characters in \c s to process
 * \param[in] rep_from The substring to replace
 * \param[in] rep_from_len The length substring to replace
 * \param[in] rep_with The substring to replace with
 * \param[in] rep_with_len The length substring to replace with
 *
 * \return The length of the new string, or 0 if an error occured
 *
 * \remark This function replaces substrings in \c str either until it has encoutered \c '\0' or it has processed \c num chars;
 *         \c rep_from and \c rep_with are not required to be null-terminated;
 *         If the resulting string is shorter than the orignal one, it will be padded with \c '\0';
 *         If the resulting string is longer than the orignal one, at most \c num chars will be written to \с s, including a terminating '\0';
 */
size_t strnrep(char* str, size_t num, char const* rep_from, size_t rep_from_len, char const* rep_with, size_t rep_with_len);

/**
 * \brief This function determines how many chars a utf-8 symbol uses if it begins with a given char
 *
 * \param[in] c The char to analyze
 *
 * \return The number of bytes a utf-8 symbol that begins with char uses, #ERROR_CHAR_NOT_BEG if a
 *         utf-8 symbol can't begin with this char, #ERROR_CHAR_NOT_VAL if this char is not valid utf-8
 */
int char_width(char c);

/**
 * \brief This function checks if a utf-8 char is alpha numeric
 *
 * \param[in] c the char to analyze
 *
 * \return 1 if the given char is alpha numeric, 0 otherwise
 */
int is_alnum(char c);

/**
 * \brief This function finds the first char for which #is_alnum is 1 or the char is '\0' in a string
 *
 * \param[in] s The string this function will analyze
 *
 * \return Pointer to the first char for which #is_alnum is 1 or the char is '\0'
 */
char const* find_alnum(char const* s);

/**
 * \brief This function compares two string ingnoring non alnum characters
 *
 * \param[in] left_str, right_str The strings this function will compare
 *
  \return < 0 if left_str < right_str, 0 if left_str == right_str, > 0 if left_str > right_str
 *
 * \remark This function considers empty strings to be greater than any other string
 */
int strcmp_alnum(char const* left_str, char const* right_str);
