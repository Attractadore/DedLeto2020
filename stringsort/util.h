/**
 * \file util.h This file defines various utility functions
 */
#pragma once

#include <stddef.h>
#include <stdio.h>

/**
 * \brief Swaps a and b
 *
 * \param t The type that will be used for the temporary variable
 * \param a, b The variables whose values will be swapped
 */
#define swap(t, a, b) \
    {                 \
        t tmp = a;    \
        a = b;        \
        b = tmp;      \
    }

/**
 * \brief This function reads all of a file's contents into a buffer
 *
 * \param[in] input_file The file from which to read
 * \param[out] buf_p Pointer to the pointer into which the address of the read buffer will be written
 *
 * \return The number of bytes read
 */
size_t read_buffer(FILE* input_file, char** buf_p);
