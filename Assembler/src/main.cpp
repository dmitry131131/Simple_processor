#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "OneginError.h"
#include "AsmErrors.h"
#include "InputOutput.h"
#include "AsmRead.h"
#include "AssemblerFunc.h"

int main(const int argc, const char* argv[])
{
    #define DESTRUCT_BUFFER_AND_RETURN do{      \
        remove_text(text);                      \
        tag_buffer_dtor(&tagBuffer);            \
        return 0;                               \
    }while(0)

    #define MAIN_ASSEMBLING(inputFile) do{                                              \
        text = asm_prepare(argv[1], &error);                                            \
        if (error)                                                                      \
        {                                                                               \
            print_assembler_error_message(error, stderr);                               \
            DESTRUCT_BUFFER_AND_RETURN;                                                 \
        }                                                                               \
                                                                                        \
        if ((error = main_assembler_function(text, &tagBuffer, inputFile)))             \
        {                                                                               \
            print_assembler_error_message(error, stderr);                               \
            DESTRUCT_BUFFER_AND_RETURN;                                                 \
        }                                                                               \
                                                                                        \
        if ((error = main_assembler_function(text, &tagBuffer, inputFile)))             \
        {                                                                               \
            print_assembler_error_message(error, stderr);                               \
            DESTRUCT_BUFFER_AND_RETURN;                                                 \
        }                                                                               \
    }while(0)

    textData* text = NULL;
    asmErrorCode error = NO_ASSEMBLER_ERRORS;        

    TagBuffer tagBuffer = {};
    if ((error = tag_buffer_ctor(&tagBuffer)))
    {
        return error;
    }

    switch (argc)
    {
    case 1:
        print_assembler_error_message(FEW_CONSOLE_ARGS, stderr);
        DESTRUCT_BUFFER_AND_RETURN;
        break;

    case 2:
        {
            char newFilename[MAX_FILENAME_SIZE] = {};

            if ((error = add_dot_bin_in_filename(argv[1], newFilename)))
            {
                print_assembler_error_message(FILENAME_ERROR, stderr);
                DESTRUCT_BUFFER_AND_RETURN;
            }

            MAIN_ASSEMBLING(newFilename);
        }
        break;

    case 4:
        {
            if (strcmp("-o", argv[2])) 
            {
                print_assembler_error_message(WRONG_CONSOLE_ARGS, stderr);
                DESTRUCT_BUFFER_AND_RETURN;
            }

            MAIN_ASSEMBLING(argv[3]);
        }
        break;
    
    default:
        break;
    }

    DESTRUCT_BUFFER_AND_RETURN;
    return 0;
}

#undef MAIN_ASSEMBLING
#undef DESTRUCT_BUFFER_AND_RETURN