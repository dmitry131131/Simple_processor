/**
 * @file
 * @brief Supporting math functions
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

const double MIN_DOUBLE_VALUE = 0.000001;

/**
 * Check nubmer is not infinity or NAN
 * @param [in] number checked value
 * @return True if number is finite and False if number is infinity
*/
int IsFinite(const double number);
/**
 * Check number != 0
 * @param [in] number checked value
 * @return True if number is zero and False if number is not zero
*/
int IsZero(const double number);
/**
 * Compare two numbers
 * @param [in] a first number
 * @param [in] b second number
 * @return True if a == b of False if a != b
*/
int EqualityNumbers(const double a, const double b); // a == b

#endif