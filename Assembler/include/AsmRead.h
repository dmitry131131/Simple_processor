/**
 * @file
 * @brief Functions that read programm file 
*/
#ifndef ASM_READ_H
#define ASM_READ_H

textData* asm_prepare(const char* filename, asmErrorCode* error);

char* add_dot_bin_in_filename(const char* filename);

#endif