/**
 * @file
 * @brief Supporting math functions
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

const double MIN_DOUBLE_VALUE = 0.000001;

processorErrorCode processor_ctor(softProcessorUnit* processor);

processorErrorCode processor_dtor(softProcessorUnit* processor);

processorErrorCode processor_verify(softProcessorUnit* processor);

processorErrorCode processor_dump(softProcessorUnit* processor);

processorErrorCode processor_CS_dump(softProcessorUnit* processor);

processorErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len);


#endif