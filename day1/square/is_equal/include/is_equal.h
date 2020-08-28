/**
 * \file is_equal.h This file implements the function isEqual
 */
#pragma once

#define DOUBLE_EQUALITY_TOLLERANCE 1e-9 /**< The tollerance value used by #isEqual */

/**
 * \brief Check if two doubles are equal within some tolerance
 *
 * \param[in] d1, d2 The doubles to compare
 *
 * \return 1 if d1 and d2 are equal within #DOUBLE_EQUALITY_TOLLERANCE, 0 otherwise
 */
int isEqual(double d1, double d2);
