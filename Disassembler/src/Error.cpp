/**
 * @file
 * @brief Functions working with processor errors sources
*/
#include <stdio.h>

#include "DisasmErrors.h"
#include "Color_output.h"

void print_disassembler_error(FILE* stream, disassemblerErrorCode error, size_t ip)
{
    print_disassembler_error_message(stream, error);
    color_fprintf(stream, COLOR_BLUE, STYLE_UNDERLINED, "Instruction pointer(IP):");
    fprintf(stream, " %lu\n", ip);
}

void print_disassembler_error_message(FILE* stream, disassemblerErrorCode error)
{
    color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Disassembler error: ");

    #define CHECK_CODE(code, message)               \
        case code:                                  \
            fprintf(stream, message);               \
            break;                                  \

    switch (error)
    {
    case NO_DISASSEMBLER_ERRORS:
        break;
    
    CHECK_CODE(FREAD_ERROR,                 "File read error, can't read information from file!\n");
    CHECK_CODE(BAD_SIGNATURE,               "Bad file signature!\n");
    CHECK_CODE(BAD_FILE_DESCRIPTOR,         "Bad file descriptor!\n");
    CHECK_CODE(VERSION_ERROR,               "Disassembler version and assembler version don't match!\n");
    CHECK_CODE(COMMAND_COUNT_ERROR,         "Command count in file header and real command count don't match!\n");
    CHECK_CODE(CALLOC_ERROR,                "Calloc error, can't alloc memory!\n");
    CHECK_CODE(READ_PROGRAMM_BODY_ERROR,    "Error in reading bytecode file body!\n");
    CHECK_CODE(FILE_OPEN_ERROR,             "Can't open file!\n");
    CHECK_CODE(BAD_FILENAME,                "Bad bytecode file!\n");
    CHECK_CODE(NULL_POINTER,                "NULL pointer given!\n");
    CHECK_CODE(DTOR_ERROR,                  "Destructor error!\n");
    CHECK_CODE(VERIFY_ERROR,                "Disassembler verification error!\n");
    CHECK_CODE(WRONG_COMMAND,               "Wrong command in bytecode file given!\n");
    CHECK_CODE(FILE_CREATING_ERROR,         "Error in creating output file!\n");
    CHECK_CODE(WRONG_FILE_CREATE_MODE,      "Wrong file creating mode given!\n");
    CHECK_CODE(FWRITE_ERROR,                "Fwrite error(error in writing buffer to output file)!\n");
    CHECK_CODE(COPU_ARG_ERROR,              "Error in copying data from buffer to variable!\n");

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }

    #undef CHECK_CODE
}
