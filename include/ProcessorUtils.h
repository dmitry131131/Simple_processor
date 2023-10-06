/**
 * @file
 * @brief Supporting math functions
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

const double MIN_DOUBLE_VALUE = 0.000001;

processorErrorCode processor_ctor(softProcessorUnit* processor, size_t commandCount);

processorErrorCode processor_dtor(softProcessorUnit* processor);

processorErrorCode processor_verify(softProcessorUnit* processor);

#endif