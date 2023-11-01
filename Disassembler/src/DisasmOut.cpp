/**
 * @file
 * @brief Functions output assembled commans sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "DisasmErrors.h"
#include "DisasmOut.h"

disassemblerErrorCode buffer_ctor(outputBuffer* buffer, size_t size)
{
    assert(buffer);

    buffer->Buffer  = NULL;
    buffer->bufferPointer = 0;
    disassemblerErrorCode error = NO_DISASSEMBLER_ERRORS;

    if ((error = create_command_buffer(&(buffer->Buffer), size)))
    {
        return error;
    }

    return error;
}

disassemblerErrorCode buffer_dtor(outputBuffer* buffer)
{
    assert(buffer);

    free(buffer->Buffer);
    buffer->Buffer  = NULL;
    buffer->bufferPointer = 0;

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode create_output_file(FILE** file, const char* filename, fileCreateMode modeCode)
{
    assert(filename);

    char mode[10] = {};
    mode[0] = 'w';
    switch (modeCode)
    {
    case BIN:
        mode[1] = 'b';
        break;

    case TEXT:
        break;
    
    default:
        return WRONG_FILE_CREATE_MODE;
    }

    *file = fopen(filename, mode);
    if (!file)
    {
        return FILE_CREATING_ERROR;
    }

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode create_command_buffer(char** buffer, size_t size)
{
    assert(buffer);

    *buffer = (char*) calloc(size + 1, sizeof(char));

    if (!buffer)
    {
        return CALLOC_ERROR;
    }

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode write_buffer_to_file(FILE* file, outputBuffer* buffer)
{
    assert(file);

    if (fwrite(buffer->Buffer, sizeof(char), buffer->bufferPointer, file) != buffer->bufferPointer)
    {
        return FWRITE_ERROR;
    }

    return NO_DISASSEMBLER_ERRORS;
}