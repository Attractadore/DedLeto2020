/**
 * \file sort.h This file defines functions that sort string arrays
 */
#pragma once

#include <stddef.h>

/**
 * \brief This function can be used to compare string array elements
 *
 * \param[in] lhs, rhs The string array elements than will be compared
 * 
 * \return -1 if lhs < rhs, 0 if lhs == rhs, 1 if lhs > rhs
 */
int cmp(void const* lhs, void const* rhs);

/**
 * \brief This functions sorts an array of strings
 *
 * \param[out] lines The string array that this function will sort
 * \param[in] num_lines The length of the string array
 */
void sort_lines(char** lines, size_t num_lines);
