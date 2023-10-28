/**
 * @file
 * @brief Main asembler functions sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "OneginError.h"
#include "InputOutput.h"
#include "AsmErrors.h"
#include "AsmOut.h"
#include "AssemblerFunc.h"

static bool check_line_availability(const char* string);

asmErrorCode main_assembler_function(textData* text, TagBuffer* tagBuffer, const char* filename)
{
    #define DEF_CMD(name, num, args, asm_code, proc_code)       \
        else if (!strcmp(command, name))                        \
        {                                                       \
            asm_code                                            \
        } 

    #define DESTRUCT_ALL_BUFFERS_AND_RETURN do{     \
                                                    \
        error = buffer_dtor(&binBuffer);            \
        error = buffer_dtor(&textBuffer);           \
                                                    \
        fclose(outputTextFile);                     \
        fclose(outputBinFile);                      \
                                                    \
    }while(0)

    assert(text);
    assert(tagBuffer);
    assert(filename);

    outputBuffer binBuffer  = {};
    outputBuffer textBuffer = {};
    asmErrorCode error      = NO_ASSEMBLER_ERRORS;

    if ((error = buffer_ctor(&binBuffer, text->bufferSize * 4)))
    {
        assert(!error);
        return error;
    }

    if ((error = buffer_ctor(&textBuffer, text->bufferSize * 10)))
    {
        assert(!error);
        return error;
    }

    FILE* outputBinFile = NULL;
    if ((error = create_output_file(&outputBinFile, filename, BIN)))
    {
        assert(!error);
        return error;
    }

    FILE* outputTextFile = NULL;
    if ((error = create_output_file(&outputTextFile, "listing", TEXT)))
    {
        assert(!error);
        return error;
    }

    size_t commandCount = 0;

    for (size_t i = 0; i < text->linesCount; i++)
    {
        char command[MAX_COMMAND_LEN]       = {};
        double commandArg                   = 0;
        char textArgName[MAX_REGISTER_LEN]  = {};

        if (!check_line_availability(text->linesPtr[i])) continue;

        if(sscanf(text->linesPtr[i], "%s", command) != 1)
        {
            error = INVALID_SYNTAX;
            print_assembler_error(error, text->linesPtr[i], i+1);
            break;
        }

        if (command[0] == ':')
        {
            add_tag_to_buffer((command + 1), (int) binBuffer.bufferPointer, tagBuffer);
        }

        #include "Functions.def"

        else
        {
            error = INVALID_SYNTAX;
            print_assembler_error(error, text->linesPtr[i], i+1);
            break;
        }
    }

    if (error)
    {
        DESTRUCT_ALL_BUFFERS_AND_RETURN;

        return error;
    }

    write_header_info(outputTextFile, outputBinFile, VERSION, commandCount);

    if ((error = write_buffer_to_file(outputBinFile, &binBuffer)))
    {
        return error;
    }

    if ((error = write_buffer_to_file(outputTextFile, &textBuffer)))
    {
        return error;
    }

    DESTRUCT_ALL_BUFFERS_AND_RETURN;

    #undef DEF_CMD
    #undef DESTRUCT_ALL_BUFFERS_AND_RETURN

    return NO_ASSEMBLER_ERRORS;
}

asmErrorCode tag_buffer_ctor(TagBuffer* tag)
{
    assert(tag);

    tag->bufferName = (Tag*) calloc(TAG_BUFFER_SIZE, sizeof(Tag));

    tag->size = 0;

    if (!tag->bufferName)
    {
        return ALLOC_MEMORY_ERROR;
    }

    return NO_ASSEMBLER_ERRORS;
}

asmErrorCode tag_buffer_dtor(TagBuffer* tag)
{
    assert(tag);

    free(tag->bufferName);

    tag->size = 0;

    return NO_ASSEMBLER_ERRORS;
}

asmErrorCode add_tag_to_buffer(const char* tagName, int ip, TagBuffer* tagBuffer)
{
    assert(tagName);
    assert(tagBuffer);

    for (size_t i = 0; i < tagBuffer->size; i++)
    {
        if (!strcmp(tagName, (tagBuffer->bufferName)[i].name))
        {
            (tagBuffer->bufferName)[i].ip = ip;
            return NO_ASSEMBLER_ERRORS;
        }
    }

    (tagBuffer->bufferName)[tagBuffer->size].ip   = ip;
    strcpy((tagBuffer->bufferName)[tagBuffer->size].name, tagName);

    (tagBuffer->size)++;

    return NO_ASSEMBLER_ERRORS;
}

asmErrorCode get_tag_ip(TagBuffer* tagBuffer, const char* tagName, int* ip)
{
    assert(tagBuffer);
    assert(tagName);

    for (size_t i = 0; i < tagBuffer->size; i++)
    {
        if (!strcmp(tagName, (tagBuffer->bufferName)[i].name))
        {
            *ip = (tagBuffer->bufferName)[i].ip;
            return NO_ASSEMBLER_ERRORS;
        }
    }

    return TAG_NOT_FOUND;
}

static bool check_line_availability(const char* string)
{
    assert(string);

    while ((*string) != 0)
    {
        if (((*string) >= 'a') && ((*string) <= 'z')) return true;
        string++;
    }

    return false;
}