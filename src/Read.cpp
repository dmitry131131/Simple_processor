#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"

processorErrorCode prepare(const char* filename, softProcessorUnit* processor)
{
    if (!filename)
    {
        return NULL_POINTER;
    }

    if (!processor)
    {
        return NULL_POINTER;
    }

    if (processor_ctor(processor))
    {
        return CTOR_ERROR;
    }

    if (read_bin_file(filename, processor))
    {
        return BIN_FILE_READ_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_bin_file(const char* filename, softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    if (!filename)
    {
        return NULL_POINTER;
    }

    FILE* file = fopen(filename, "rb");

    if (!file)
    {
        return FILE_OPEN_ERROR;
    }

    struct stat fileInfo = {};

    if (fstat(fileno(file), &fileInfo))
    {
        return BAD_FILE_DESCRIPTOR;
    }

    size_t fileSize = fileInfo.st_size;

    processor->CS = (char*) calloc(fileSize, sizeof(char));

    if (!(processor->CS))
    {
        return CALLOC_ERROR;
    }

    processorErrorCode err = NO_PROCESSOR_ERRORS;

    char signature[10] = {};
    int version = 0;

    if ((err = read_char_from_file(file, signature)))
    {
        return err;
    }
    if (err = read_char_from_file(file, signature + 1))
    {
        return err;
    }

    if (signature[0] != 'A' || signature[1] != 'D')
    {
        return BAD_SIGNATURE;
    }

    if (err = read_int_from_file(file, &version))
    {
        return err;
    }

    if (version != VERSION)
    {
        return VERSION_ERROR;
    }

    int count = 0;
    if (err = read_int_from_file(file, &count))
    {
        return err;
    }

    if (count <= 0)
    {
        return COMMAND_COUNT_ERROR;
    }

    processor->commandCount = (size_t) count;

    if (err = read_programm_body(file, &(processor->CS), fileSize))

    fclose(file);
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_programm_body(FILE* file, char** buff, size_t len)
{
    if (!file)
    {
        return NULL_POINTER;
    }

    if (!buff)
    {
        return NULL_POINTER;
    }

    if (fread(*buff, sizeof(char), len, file))
    {
        return FREAD_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_char_from_file(FILE* file, char* ch)
{
    if (!file)
    {
        return NULL_POINTER;
    }

    if (fread(ch, sizeof(char), 1, file) != 1)
    {
        return FREAD_ERROR;
    }
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_int_from_file(FILE* file, int* num)
{
    if (!file)
    {
        return NULL_POINTER;
    }

    if (fread(num, sizeof(int), 1, file) != 1)
    {
        return FREAD_ERROR;
    }
    return NO_PROCESSOR_ERRORS;
}