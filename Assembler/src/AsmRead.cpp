/**
 * @file
 * @brief Functions that read programm file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "OneginError.h"
#include "AsmErrors.h"
#include "InputOutput.h"
#include "AsmRead.h"

static textData* text_to_lower(textData* text);
static textData* remove_comments_from_text(textData* text);

textData* asm_prepare(const char* filename, asmErrorCode* error)
{
    assert(filename);

    static textData text = {};
    errorCode err = NO_ERRORS;

    err = get_text(filename, &text);

    if (err)
    {
        print_filename(stderr, filename);
        print_error_message(stderr, err);
        *error = WRONG_CONSOLE_ARGS;
    }

    text_to_lower(&text);

    remove_comments_from_text(&text);

    return &text;
}

static textData* text_to_lower(textData* text)
{
    assert(text);

    for (size_t i = 0; i < text->bufferSize; i++)
    {
        text->bufferName[i] = (char) tolower(text->bufferName[i]);
    }

    return text;
}

static textData* remove_comments_from_text(textData* text)
{
    assert(text);

    for (size_t i = 0; i < text->bufferSize; i++)
    {
        if (text->bufferName[i] == ';')
        {
            text->bufferName[i] = 0;
        }
    }

    return text;
}

char* add_dot_bin_in_filename(const char* filename)
{
    assert(filename);

    size_t len = strlen(filename);
    char* newFilename = (char*) calloc(len + 5, sizeof(char));

    if (!newFilename) return NULL;

    strcpy(newFilename, filename);

    strcat(newFilename, ".bin");

    return newFilename;
}