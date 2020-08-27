#include "is_equal.h"

#include <math.h>

int isEqual(double d1, double d2)
{
    return islessequal(fabs(d1 - d2), DOUBLE_EQUALITY_TOLLERANCE);
}
