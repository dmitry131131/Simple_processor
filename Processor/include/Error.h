/**
 * @file
 * @brief Functions working with processor errors
*/
#ifndef ERROR_H
#define ERROR_H

const int VERSION = 2;

enum processorErrorCode {
    NO_PROCESSOR_ERRORS,
    WRONG_COMMAND,
    WRONG_NUMBER,
    CTOR_ERROR,
    PUSH_ERROR,
    POP_ERROR,
    DIVIDION_BY_ZERO,
    FILE_OPEN_ERROR,
    FREAD_ERROR,
    BAD_SIGNATURE,
    BAD_FILE_DESCRIPTOR,
    NULL_POINTER,
    VERSION_ERROR,
    COMMAND_COUNT_ERROR,
    BIN_FILE_READ_ERROR,
    DTOR_ERROR,
    COPU_ARG_ERROR,
    VERIFY_ERROR,
    STACK_CTOR_ERROR,
    CALLOC_ERROR,
    READ_PROGRAMM_BODY_ERROR,
    BAD_FILENAME,
    BAD_IP,
    BAD_ADRESS
};

void print_processor_error_message(FILE* stream, processorErrorCode error);

void print_processor_error(FILE* stream, processorErrorCode error, size_t ip);

#endif