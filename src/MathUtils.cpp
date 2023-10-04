#include <math.h>

#include "MathUtils.h"  


int IsFinite(const double number)
{
    return !isnan(number) && !isinf(number);
}

int IsZero(const double number)
{
    return !(fabs(number) > MIN_DOUBLE_VALUE);
}

int EqualityNumbers(const double a, const double b)
{
    return !(fabs(a - b) > MIN_DOUBLE_VALUE);
}