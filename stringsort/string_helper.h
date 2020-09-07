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