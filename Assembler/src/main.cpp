#include <stdio.h>

#include "OneginError.h"
#include "AsmErrors.h"
#include "InputOutput.h"
#include "AsmRead.h"
#include "AssemblerFunc.h"

int main(const int argc, const char* argv[])
{
    textData* text = NULL;
    asmErrorCode error = NO_ASSEMBLER_ERRORS;

    #define DESTRUCT_BUFFER_AND_RETURN do{      \
        remove_text(text);                      \
        tag_buffer_dtor(&tagBuffer);            \
        return 0;                               \
    }while(0)           

    TagBuffer tagBuffer = {};
    if ((error = tag_buffer_ctor(&tagBuffer)))
    {
        return error;
    }

    if (argc == 1)
    {
        print_assembler_error_message(FEW_CONSOLE_ARGS, stderr);
        DESTRUCT_BUFFER_AND_RETURN;
    }

    for (int i = 1; i < argc; i++)
    {
        text = asm_prepare(argv[i]);
        if ((error = main_assembler_function(text, &tagBuffer)))
        {
            print_assembler_error_message(error, stderr);
            DESTRUCT_BUFFER_AND_RETURN;
        }
        if ((error = main_assembler_function(text, &tagBuffer)))
        {
            print_assembler_error_message(error, stderr);
            DESTRUCT_BUFFER_AND_RETURN;
        }
    }

    DESTRUCT_BUFFER_AND_RETURN;
    return 0;
}