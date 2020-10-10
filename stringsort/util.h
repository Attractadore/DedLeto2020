/**
 * \file util.h This file defines various utility functions
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef int (*comparator)(void const*, void const*);
typedef void (*sorter)(void*, size_t, size_t, comparator);

/**
 * \brief Swaps a and b
 *
 * \param t The type that will be used for the temporary variable
 * \param a, b The variables whose values will be swapped
 */
#define swap(t, a, b) \
    do {              \
        t tmp = a;    \
        a = b;        \
        b = tmp;      \
    } while (0)

/**
 * \brief This functions swaps the contents of two areas of memory
 *
 * \param[in, out] a, b The pointers to the blocks of memory whose contents will be swapped
 * \param[in] num The size of the blocks of memory whose contents will be swapped
 *
 * \remark Behaviour is undefined if \c a and \b overlap
 */
void memswap(void* a, void* b, size_t num);

/**
 * \brief This function reads all of a file's contents into a buffer
 *
 * \param[in] input_file The file from which to read
 * \param[out] buf_p Pointer to the pointer into which the address of the read buffer will be written
 *
 * \return The number of bytes read
 */
size_t read_buffer(FILE* input_file, char** buf_p);

/**
 * \brief This function checks if an array is sorted based on some critertion
 *
 * \param[in] arr The array to check
 * \param[in] num The number of elements in the array
 * \param[in] sz The size of each of the array's elements
 * \param[in] comp The function to use to compare elements
 *
 * \return 0 if the array if not sorted, not 0 otherwise
 */
bool is_sorted(void const* arr, size_t num, size_t sz, comparator comp);

/**
 * \brief This function sorts an array using the quicksort algorithm
 *
 * \param[in] arr The array to sort
 * \param[in] num The number of elements in the array
 * \param[in] sz The size of each of the array's elements
 * \param[in] comp The function to use to compare elements
 */
void quick_sort(void* arr, size_t num, size_t sz, comparator comp);
