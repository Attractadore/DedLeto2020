/**
 * \file lines.h This file defines functions for working with arrays of strings
 */
#pragma once
#include <stdio.h>

/**
 * \brief This function frees an array of strings
 *
 * \param[out] lines The string array that this function will operate on
 * \param[in] num_lines The length of the string array
 *
 * \remark This function frees both the string array and every string that it contains
 */
void free_lines(char** lines, size_t num_lines);

/**
 * \brief This function reads lines and stores them in an array
 *
 * \param[in] input_stream The stream from which the lines will be read
 * \param[out] lines_p Pointer to array of strings where the lines will be stored
 *
 * \return The number of lines read
 *
 * \remark You must free the array of lines that this function returns manually or by calling #free_lines.
 *         This function reads lines until it encouters EOF
 */
size_t read_lines(FILE* input_stream, char*** lines_p);
