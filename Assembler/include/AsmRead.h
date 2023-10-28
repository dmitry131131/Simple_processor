/**
 * @file
 * @brief Functions that read programm file 
*/
#ifndef ASM_READ_H
#define ASM_READ_H

const char   BIN_EXTENTION[]      = ".bin";
const size_t BIN_EXTENTION_SIZE = 4;
const size_t MAX_FILENAME_SIZE  = 250;

textData* asm_prepare(const char* filename, asmErrorCode* error);

asmErrorCode add_dot_bin_in_filename(const char* filename, char* newFilename);

#endif