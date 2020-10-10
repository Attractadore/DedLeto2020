/**
 * \file lines.h This file contains functions for accessing the program's core functionality
 */
#pragma once

#include <stdio.h>

typedef enum stringsort_error_enum {
    SORT_OK,
    SORT_READ_ERROR,
    SORT_WRITE_ERROR,
    SORT_EXEC_ERROR
} STRINGSORT_ERROR;

/**
 * \brief This function reads an input file's contents, sorts them and writes them to a output file
 *
 * \param[in] input_file, output_file The files this function will operate on
 *
 * \return an error code describing what kind of error, if any, occured
 */
STRINGSORT_ERROR stringsort(FILE* input_file, FILE* output_file);

/**
 * \brief This function returns a string corresponding to a given error code
 *
 * \param[in] err The error code
 * 
 * \return Human-readable representation of the given error code
 */
char const* get_stringsort_error(STRINGSORT_ERROR err);
