/**
 * @file
 * @brief Output functions
*/
#ifndef DISASM_OUT_H
#define DISASM_OUT_H

enum fileCreateMode {
    BIN,
    TEXT
};

struct outputBuffer {
    char* Buffer;
    size_t bufferPointer;
};

disassemblerErrorCode buffer_ctor(outputBuffer* buffer, size_t size);

disassemblerErrorCode write_buffer_to_file(FILE* file, outputBuffer* buffer);

disassemblerErrorCode buffer_dtor(outputBuffer* buffer);

disassemblerErrorCode create_output_file(FILE** file, const char* filename, fileCreateMode modeCode);

disassemblerErrorCode create_command_buffer(char** buffer, size_t size);

#endif