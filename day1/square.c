#include <math.h>
#include <stdio.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define NO_ERROR 0
#define SOLUTION_ERROR 1
#define INPUT_ERROR 2

#define EQ_INFINITE_SOLUTIONS 3
#define EQ_ERROR_SOLUTIONS -1

#define DOUBLE_EQUALITY_TOLLERANCE 1e-9

int isEqual(double d1, double d2)
{
    return fabs(d1 - d2) <= DOUBLE_EQUALITY_TOLLERANCE;
}

int solveEquation(double a, double b, double c, double* x1p, double* x2p)
{
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
        double solution = -c / b;
        if (x1p)
            *x1p = solution;
        if (x2p)
            *x2p = solution;
        return 1;
    }

    b /= a;
    c /= a;
    a = 1;

    double D = b * b - 4 * c;
    if (D < 0) {
        return 0;
    } else if (isEqual(D, 0)) {
        double solution = -b / 2;
        if (x1p)
            *x1p = solution;
        if (x2p)
            *x2p = solution;
        return 1;
    }
    double sD = sqrt(D);
    if (x1p)
        *x1p = (-b - sD) / 2;
    if (x2p)
        *x2p = (-b + sD) / 2;
    return 2;
}

int main()
{
    double a, b, c, x1, x2;
    a = b = c = x1 = x2 = 0;
    printf("Equation solver %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    printf("Enter equation coefficients:\n");
    int stat;
    stat = scanf("%lg %lg %lg", &a, &b, &c);

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
