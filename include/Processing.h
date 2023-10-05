/**
 * @file
 * @brief Main functions or processor
*/
#ifndef PROCESSING_H
#define PROCESSING_H

const int DOUBLE_COEF = 10000;

/**
 * @brief Main processing function
 * @param [in] text Pointer to programm text
 * @return Error code or NO_ERRORS if everything is ok
*/
enum processorErrorCode processing(textData* text);

enum processorErrorCode processor_push(const char* line, Stack* stack);

enum processorErrorCode processor_out(Stack* stack, FILE* stream);

enum processorErrorCode processor_add(Stack* stack);

enum processorErrorCode processor_sub(Stack* stack);

enum processorErrorCode processor_mue(Stack* stack);

enum processorErrorCode processor_div(Stack* stack);

enum processorErrorCode processor_sqrt(Stack* stack);

enum processorErrorCode processor_trig(Stack* stack, int mode);

enum processorErrorCode processor_in(Stack* stack, FILE* inputStream);

enum processorErrorCode processor_hlt(Stack* stack);

#endif