/**
 * \file lines.h This file defines functions for working with arrays of strings
 */
#pragma once
#include <stdio.h>

struct _lines_s {
    char** _lines;
    size_t _num_lines;
    char* _string_buffer;
    size_t _string_buffer_size;
};

/**
 * This structure represents strings that have been stored in a buffer. Do not modify it directly
 */
typedef struct _lines_s LINES;

/**
 * \brief This function reads lines and stores them in a #LINES structure
 *
 * \param[in] input_file The file from which the lines will be read
 *
 * \return A #LINES structure describing the read lines
 *
 * \remark You can free the returned structure by calling #free_lines.
 *         This function reads lines until it encouters EOF
 */
LINES* read_lines(FILE* input_file);

/**
 * \brief This function reverses the contents of a #LINES structure without changing their order
 *
 * \param[in] lines The #LINES structure whose contents this this function will operate on
 */
void reverse_lines(LINES* lines);

/**
 * \brief This functions writes the contents of a #LINES structure to a file
 *
 * \param[in] lines The #LINES structure whose contents that this function will write
 * \param[in] file The file to which the lines will be written 
 */
void write_lines(const LINES* lines, FILE* file);

/**
 * \brief This function sorts the contents of a #LINES structure
 *
 * \param[in, out] lines The #LINES structure whose contents will be sorted by this function
 */
void sort_lines(LINES* lines);

/**
 * \brief This function frees the #LINES structure returned by #read_lines
 *
 * \param[out] lines The #LINES structure that this function will operate on
 */
void free_lines(LINES* lines);
