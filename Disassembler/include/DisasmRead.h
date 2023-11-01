/**
 * @file
 * @brief Read bin file functions
*/
#ifndef DISASM_READ_H
#define DISASM_READ_H

const size_t FILE_HEADER_LEN = 10;

disassemblerErrorCode prepare(const char* filename, disassemblerCase* disasmCase);

disassemblerErrorCode read_bin_file(const char* filename, disassemblerCase* disasmCase);

disassemblerErrorCode read_programm_body(FILE* file, char** buff, size_t len);

disassemblerErrorCode read_char_from_file(FILE* file, char* ch);

disassemblerErrorCode read_int_from_file(FILE* file, int* num);

disassemblerErrorCode filename_getter(int argc, char* argv[], char** filename);

#endif