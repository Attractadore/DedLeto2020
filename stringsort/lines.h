/**
 * \file lines.h This file defines functions for working with arrays of strings
 */
#pragma once
#include <stdio.h>

struct _lines_s {
    char const** lines;
    size_t num_lines;
    char* _string_buffer;
    size_t _string_buffer_size;
};

typedef struct _lines_s LINES;

/**
 * \brief This function reads lines and stores
 *
 * \param[in] input_stream The stream from which the lines will be read
 *
 * \return A #LINES structure describing the read lines
 *
 * \remark You can free the returned structure by calling #free_lines.
 *         This function reads lines until it encouters EOF
 */
LINES* read_lines(FILE* input_stream);

/**
 * \brief This functions writes the contents of a #LINES structure to a file
 *
 * \param[in] lines The #LINES structure whose contents that this function will write
 */
void write_lines(const LINES* lines, FILE* file);

/**
 * \brief This function sorts the contents of a #LINES structure;
 *
 * \param[in, out] lines The #LINES structure whose contents will be sorted by this function
 */
void sort_lines(LINES* lines);

/**
 * \brief This function free the #LINES structure returned by #read_lines
 *
 * \param[out] lines The #LINES structure that this function will operate on
 */
void free_lines(LINES* lines);
