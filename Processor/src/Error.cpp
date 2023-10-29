/**
 * @file
 * @brief Functions working with processor errors sources
*/
#include <stdio.h>

#include "Error.h"
#include "Color_output.h"

void print_processor_error(FILE* stream, processorErrorCode error, size_t ip)
{
    print_processor_error_message(stream, error);
    color_fprintf(stream, COLOR_BLUE, STYLE_UNDERLINED, "Instruction pointer(IP):");
    fprintf(stream, " %lu\n", ip);
}

void print_processor_error_message(FILE* stream, processorErrorCode error)
{
    color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Processor error: ");

    #define CHECK_CODE(code, message)               \
        case code:                                  \
            fprintf(stream, message);               \
            break;                                  \

    switch (error)
    {
    case NO_PROCESSOR_ERRORS:
        break;
    
    CHECK_CODE(WRONG_COMMAND,               "Unknown command entered!\n");
    CHECK_CODE(WRONG_NUMBER,                "Wrong number entered!\n");
    CHECK_CODE(CTOR_ERROR,                  "Stack constructor error!\n");
    CHECK_CODE(PUSH_ERROR,                  "Push in stack error!\n");
    CHECK_CODE(POP_ERROR,                   "Pop from stack error!\n");
    CHECK_CODE(DIVIDION_BY_ZERO,            "Dividion by zero!\n");
    CHECK_CODE(FREAD_ERROR,                 "File read error, can't read information from file!\n");
    CHECK_CODE(BAD_SIGNATURE,               "Bad file signature!\n");
    CHECK_CODE(BAD_FILE_DESCRIPTOR,         "Bad file descriptor!\n");
    CHECK_CODE(NULL_POINTER,                "NULL pointer given!\n");
    CHECK_CODE(VERSION_ERROR,               "Processor version and assembler version don't match!\n");
    CHECK_CODE(COMMAND_COUNT_ERROR,         "Command count in file header and real command count don't match!\n");
    CHECK_CODE(BIN_FILE_READ_ERROR,         "Fread error with BIN file!\n");
    CHECK_CODE(DTOR_ERROR,                  "Destructor error!\n");
    CHECK_CODE(COPU_ARG_ERROR,              "Copy argument from buffer to variable error!\n");
    CHECK_CODE(VERIFY_ERROR,                "Processor verification error!\n");
    CHECK_CODE(STACK_CTOR_ERROR,            "Stack constructor error!\n");
    CHECK_CODE(CALLOC_ERROR,                "Calloc error, can't alloc memory!\n");
    CHECK_CODE(READ_PROGRAMM_BODY_ERROR,    "Error in reading bytecode file body!\n");
    CHECK_CODE(FILE_OPEN_ERROR,             "Can't open file!\n");
    CHECK_CODE(BAD_FILENAME,                "Bad bytecode file!\n");
    CHECK_CODE(BAD_IP,                      "Bad instruction pointer(IP) given!\n");
    CHECK_CODE(BAD_ADRESS,                  "Bad adress in RAM given!\n");

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }

    #undef CHECK_CODE
}
