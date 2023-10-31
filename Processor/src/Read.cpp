#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"

processorErrorCode prepare(const char* filename, softProcessorUnit* processor)
{
    assert(filename);
    assert(processor);

    processorErrorCode error = NO_PROCESSOR_ERRORS;

    if ((error = processor_ctor(processor)))
    {
        return error;
    }

    if ((error = read_bin_file(filename, processor)))
    {
        return error;
    }

    return error;
}

processorErrorCode read_bin_file(const char* filename, softProcessorUnit* processor)
{
    assert(processor);
    assert(filename);

    FILE* file = fopen(filename, "rb");

    #define RETURN(err) do{     \
        fclose(file);           \
        return err;             \
    }while(0);

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
        RETURN(CALLOC_ERROR);
    }

    processorErrorCode err = NO_PROCESSOR_ERRORS;

    char signature[10] = {};
    int version = 0;

    if ((err = read_char_from_file(file, signature)))
    {
        RETURN(err);
    }
    if ((err = read_char_from_file(file, signature + 1)))
    {
        RETURN(err);
    }

    if (signature[0] != 'A' || signature[1] != 'D')
    {
        RETURN(BAD_SIGNATURE);
    }

    if ((err = read_int_from_file(file, &version)))
    {
        RETURN(err);
    }

    if (version != VERSION)
    {
        RETURN(VERSION_ERROR);
    }

    int count = 0;
    if ((err = read_int_from_file(file, &count)))
    {
        RETURN(err);
    }

    if (count <= 0)
    {
        RETURN(COMMAND_COUNT_ERROR);
    }

    processor->commandCount = (size_t) count;

    if ((err = read_programm_body(file, &(processor->CS), fileSize - FILE_HEADER_LEN)))
    {
        RETURN(READ_PROGRAMM_BODY_ERROR);
    }

    fclose(file);

    #undef RETURN
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_programm_body(FILE* file, char** buff, size_t len)
{
    assert(file);
    assert(buff);

    size_t realLen = fread(*buff, sizeof(char), len, file);
    if (realLen != len)
    {
        return FREAD_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_char_from_file(FILE* file, char* ch)
{
    assert(file);

    if (fread(ch, sizeof(char), 1, file) != 1)
    {
        return FREAD_ERROR;
    }
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode read_int_from_file(FILE* file, int* num)
{
    assert(file);

    if (fread(num, sizeof(int), 1, file) != 1)
    {
        return FREAD_ERROR;
    }
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode filename_getter(int argc, char* argv[], char** filename)
{
    assert(argv);
    assert(filename);
    
    if (argc < 2)
    {
        return BAD_FILENAME;
    }

    *filename = argv[1];

    return NO_PROCESSOR_ERRORS;
}