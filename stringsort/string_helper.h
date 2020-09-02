/**
 * \file string_helper.h This file defines helper function for working with strings and characters
 */
#pragma once
#include <stddef.h>

#define STR_REV_SUCCESS 0
#define STR_REV_ERROR -1

#define ERROR_CHAR_NOT_BEG 0
#define ERROR_CHAR_NOT_VAL -1

/**
 * \brief This function reverses a utf-8 string in place
 *
 * \param[in, out] s The string that will be reversed
 * 
 * \return #STR_REV_SUCCESS if reversed string, #STR_REV_ERROR otherwise
 */
int string_reverse(char* s);

/**
 * \brief This function determines how many chars a utf-8 symbol uses if it begins with the given char
 *
 * \param[in] c The char to analyze
 *
 * \return The number of bytes a utf-8 symbol that begins with char uses, #ERROR_CHAR_NOT_BEG if a
 *         utf-8 symbol can't begin with this char, #ERROR_CHAR_NOT_VAL if this char is not valid utf-8.
 */
int char_width(char c);

/**
 * \brief This function checks if a char is alnum
 *
 * \param[in] c the char to analyze
 *
 * \return 1 if 
 */
int is_good(char c);

/**
 * \brief This function finds the first char for which #is_good is 1 or the char is '\0' in a string
 *
 * \param[in] s The string this function will analyze
 * \param[in] i The index of the char this function will analyze
 *
 * \return The index of the first char for which #is_good is 1 or the char is '\0'
 */
size_t find_good(char const* s, size_t i);

/**
 * \brief This function compares two string ingnoring non alnum characters
 *
 * \param[in] left_value_p, right_value_p Pointers to the strings this function will compare
 *
 * \return -1 if *left_value_p < *right_value_p, 0 if *left_value_p == right_value_p, 1 if *left_value_p > *right_value_p
 *
 * \remark This function considers empty strings to be greater than any other string
 */
int cmp_str(void const* left_value_p, void const* right_value_p);
