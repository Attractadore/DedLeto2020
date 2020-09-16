/**
 * \file file.h This file defines functions that simplify working with files
 */
#pragma once

#include <stdio.h>

/**
 * \brief This function opens files
 *
 * \param[in] file_name The name of the file to open
 * \param[in] mode Specifies how the file will be accessed
 *
 * \return FILE* if the file was successfully opened, NULL otherwise
 *
 * \remark file_name can be stdin, stdout or stderr;
 *         mode takes the same values as fopen's mode parameter;
 *         Trying to open stdin in modes other than "r" or "rb"
 *         and stdout or stderr in modes other than "w", "wb", "a" or "ab"
 *         will result in an error
 */
FILE* open_file(const char* file_name, const char* mode);

/**
 * \brief This function closes files opened by #open_file
 *
 * \param[in] file File pointer describing the file to close
 *
 * \return 0 if successfully closed file, EOF otherwise
 *
 * \remark Trying to close stdin, stdout or stderr will result in an error
 */
int close_file(FILE* file);
