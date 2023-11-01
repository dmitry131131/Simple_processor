/**
 * @file
 * @brief Error handling functions
*/
#ifndef DISASM_ERRORS_H
#define DISASM_ERRORS_H

enum disassemblerErrorCode{
    NO_DISASSEMBLER_ERRORS,
    BAD_FILENAME,
    FREAD_ERROR,
    READ_PROGRAMM_BODY_ERROR,
    COMMAND_COUNT_ERROR,
    VERSION_ERROR,
    BAD_SIGNATURE,
    CALLOC_ERROR,
    BAD_FILE_DESCRIPTOR,
    FILE_OPEN_ERROR,
    VERIFY_ERROR,
    NULL_POINTER,
    DTOR_ERROR,
    WRONG_COMMAND,
    FILE_CREATING_ERROR,
    WRONG_FILE_CREATE_MODE,
    FWRITE_ERROR,
    COPU_ARG_ERROR

};

void print_disassembler_error(FILE* stream, disassemblerErrorCode error, size_t ip);

void print_disassembler_error_message(FILE* stream, disassemblerErrorCode error);

#endif