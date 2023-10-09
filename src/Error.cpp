/**
 * @file
 * @brief Functions working with processor errors sources
*/
#include <stdio.h>

#include "Error.h"
#include "Color_output.h"

void print_processor_error(FILE* stream, processorErrorCode error)
{
    print_processor_error_message(stream, error);
}

void print_processor_error_message(FILE* stream, processorErrorCode error)
{
    color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Processor error: ");

    #define CHECK_CODE(error, code, message) do{    \
        if ((error) == (code))                      \
        {                                           \
            fprintf(stream, message);               \
        }                                           \
    }while(0)

    CHECK_CODE(error, WRONG_COMMAND, "Unknown command entered!\n");
    CHECK_CODE(error, WRONG_NUMBER, "Wrong number entered!\n");
    CHECK_CODE(error, CTOR_ERROR, "Stack constructor error!\n");
    CHECK_CODE(error, PUSH_ERROR, "Push in stack error!\n");
    CHECK_CODE(error, POP_ERROR, "Pop from stack error!\n");
    CHECK_CODE(error, DIVIDION_BY_ZERO, "Dividion by zero!\n");
    CHECK_CODE(error, FREAD_ERROR, "File read error, can't read information from file!\n");
    CHECK_CODE(error, BAD_SIGNATURE, "Bad file signature!\n");
    CHECK_CODE(error, BAD_FILE_DESCRIPTOR, "Bad file descriptor!\n");
    CHECK_CODE(error, NULL_POINTER, "NULL pointer given!\n");
    CHECK_CODE(error, VERSION_ERROR, "Processor version and assembler version don't match!\n");
    CHECK_CODE(error, COMMAND_COUNT_ERROR, "Command count in file header and real command count don't match!\n");
    CHECK_CODE(error, BIN_FILE_READ_ERROR, "Fread error with BIN file!\n");
    CHECK_CODE(error, DTOR_ERROR, "Destructor error!\n");
    CHECK_CODE(error, COPU_ARG_ERROR, "Copy argument from buffer to variable error!\n");
    CHECK_CODE(error, VERIFY_ERROR, "Processor verification error!\n");
    CHECK_CODE(error, STACK_CTOR_ERROR, "Stack constructor error!\n");
    CHECK_CODE(error, CALLOC_ERROR, "Calloc error, can't alloc memory!\n");
    CHECK_CODE(error, READ_PROGRAMM_BODY_ERROR, "Error in reading bytecode file body!\n");
    CHECK_CODE(error, FILE_OPEN_ERROR, "Can't open file!\n");
    CHECK_CODE(error, BAD_FILENAME, "Bad bytecode file!\n");

    #undef CHECK_CODE
}
