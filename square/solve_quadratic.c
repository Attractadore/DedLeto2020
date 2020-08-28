#include "solve_quadratic.h"
#include "is_equal.h"

#include <assert.h>
#include <math.h>

int solveQuadratic(double a, double b, double c, double* x1p, double* x2p) {
    assert(x1p);
    assert(x2p);
    assert(x1p != x2p);

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
        double sqrtC = sqrt(-c);
        *x1p = -sqrtC;
        *x2p = sqrtC;
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
    double sqrtD = sqrt(D);
    *x1p = (-b - sqrtD) / 2;
    *x2p = (-b + sqrtD) / 2;
    return 2;
}
