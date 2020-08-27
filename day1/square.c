/**
 *  \file square.c Program that solves a quadratic equation
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define NO_ERROR 0
#define SOLUTION_ERROR 1
#define INPUT_ERROR 2

#define DOUBLE_EQUALITY_TOLLERANCE 1e-9

#define EQ_INFINITE_SOLUTIONS 3 /**< Symbolic parameter indicating that an infinite number of solution was found */
#define EQ_ERROR_SOLUTIONS -1 /**< Symbolic parameter indicating that an error occured while trying to find a solution */

/**
 * \brief Check that two doubles are equal within some tolerance
 *
 * \param[in] d1, d2 The doubles being compared
 *
 * \return 1 if d1 and d2 are equal within some tolerance, 0 otherwise
 */
int isEqual(double d1, double d2)
{
    return islessequal(fabs(d1 - d2), DOUBLE_EQUALITY_TOLLERANCE);
}

/**
 * \brief Solve a quadratic equation
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
int solveEquation(double a, double b, double c, double* x1p, double* x2p)
{
    assert(x1p);
    assert(x2p);

    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return EQ_ERROR_SOLUTIONS;
    }

    if (isEqual(a, 0)) {
        if (isEqual(b, 0)) {
            if (isEqual(c, 0)) {
                return EQ_INFINITE_SOLUTIONS;
            }
            return 0;
        }
        *x1p = *x2p = -c / b;
        return 1;
    }

    b /= a;
    c /= a;

    if (isEqual(b, 0)) {
        if (c > 0) {
            return 0;
        } else if (isEqual(c, 0)) {
            *x1p = *x2p = 0;
            return 1;
        }
        *x1p = -(*x2p = sqrt(-c));
        return 2;
    }

    if (isEqual(c, 0)) {
        *x1p = fmin(0, -b);
        *x2p = fmax(0, -b);
        return 2;
    }

    double D = b * b - 4 * c;
    if (D < 0) {
        return 0;
    } else if (isEqual(D, 0)) {
        *x1p = *x2p = -b / 2;
        return 1;
    }
    double sD = sqrt(D);
    *x1p = (-b - sD) / 2;
    *x2p = (-b + sD) / 2;
    return 2;
}

int main()
{
    double a = 0,
           b = 0,
           c = 0,
           x1 = 0,
           x2 = 0;
    printf("Equation solver version %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    printf("I solve ax^2 + bx + c = 0\n");
    printf("Enter a b c:\n");

    int stat = scanf("%lg %lg %lg", &a, &b, &c);
    if (stat != 3) {
        printf("Sorry, did not get that\n");
        return INPUT_ERROR;
    }

    int numSolutions = solveEquation(a, b, c, &x1, &x2);
    switch (numSolutions) {
    case 0:
        printf("No solutions\n");
        break;
    case 1:
        printf("x = %g\n", x1);
        break;
    case 2:
        printf("x1 = %g x2 = %g\n", x1, x2);
        break;
    case EQ_INFINITE_SOLUTIONS:
        printf("Infinite number of solutions\n");
        break;
    default:
        printf("Error while trying to solve equation\n");
        return SOLUTION_ERROR;
    }

    return NO_ERROR;
}
