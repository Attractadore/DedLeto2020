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
 * \brief This macro allows you to use existing comparison functions with qsort
 *
 * \param t The type of the arguments the base comparison function uses
 * \param compare_f The name of the base comparison function
 * \param adapt_f The name of the adapted comparison function
 *
 * \remark This macro defines the function adapt_f
 */
#define qsort_adapt_f(t, compare_f, adapt_f)                              \
    int adapt_name(void const* left_value_p, void const* right_value_p) { \
        t const* left_p = left_value_p;                                   \
        t const* right_p = right_value_p;                                 \
        return compare_f(*left_p, *right_p);                              \
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
