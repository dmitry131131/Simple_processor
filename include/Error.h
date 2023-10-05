/**
 * @file
 * @brief Functions working with processor errors
*/
#ifndef ERROR_H
#define ERROR_H

enum processorErrorCode {
    NO_PROCESSOR_ERRORS,
    WRONG_COMMAND,
    WRONG_NUMBER,
    CTOR_ERROR,
    PUSH_ERROR,
    POP_ERROR,
    DIVIDION_BY_ZERO
};

void print_processor_error_message(FILE* stream, processorErrorCode error);

void print_processor_error(FILE* stream, processorErrorCode error, size_t line, const char* text);

#endif