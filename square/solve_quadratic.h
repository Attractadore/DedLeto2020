#pragma once
/**
 * \file solve_quadratic.h This file defines a function that solves quadratic equations
 */

#define EQ_INFINITE_SOLUTIONS 3 /**< Symbolic parameter indicating that an infinite number of solutions was found */
#define EQ_ERROR_SOLUTIONS -1   /**< Symbolic parameter indicating that an error occured while trying to find a solution */

/**
 * \brief Solves a quadratic equation
 *
 * \param[in] a The term before x^2
 * \param[in] b The term before x
 * \param[in] c The free term
 * \param[out] x1p Where to store the first solution
 * \param[out] x2p Where to store the second solution
 *
 * \return The number of solutions, or #EQ_INFINITE_SOLUTIONS if there are infinitely many solutions,
 *         or #EQ_ERROR_SOLUTIONS if an error occured while trying to solve the equation
 */
int solveQuadratic(double a, double b, double c, double* x1p, double* x2p);
