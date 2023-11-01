#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "DisasmErrors.h"
#include "Disassembling.h"
#include "DisassemblerUtils.h"
#include "DisasmOut.h"

disassemblerErrorCode disassembling(disassemblerCase* disasmCase)
{
    #define DEF_CMD(name, num, arg, asm_code, proc_code, dis_code)      \
        case num:                                                       \
            dis_code                                                    \
            break;                    

    #define DESTRUCT_ALL_BUFFERS do{                \
                                                    \
        buffer_dtor(&textBuffer);                   \
                                                    \
        fclose(outputTextFile);                     \
                                                    \
    }while(0)     

    disassemblerErrorCode err = NO_DISASSEMBLER_ERRORS;                 

    outputBuffer textBuffer = {};
    if ((err = buffer_ctor(&textBuffer, disasmCase->commandCount * 100)))
    {
        return err;
    }

    FILE* outputTextFile = NULL;
    if ((err = create_output_file(&outputTextFile, "Disassembled_file.txt", TEXT)))
    {
        return err;
    }

    commandCodes command = NO_COMMAND;
    double commandArg = NAN;
    registerNames reg = NO_REG;
    while (disasmCase->IP < disasmCase->CS_len)
    {
        command = (commandCodes) *(disasmCase->CS + disasmCase->IP);

        switch (command & COMMAND_PART)
        {
        
        #include "Functions.def"
        
        default:
            err = WRONG_COMMAND;
            break;
        }

        if (err)
        {
            DESTRUCT_ALL_BUFFERS;
            return err;
        }
    }

    if ((err = write_buffer_to_file(outputTextFile, &textBuffer)))
    {
        DESTRUCT_ALL_BUFFERS;
        return err;
    }

    DESTRUCT_ALL_BUFFERS;
    return NO_DISASSEMBLER_ERRORS;

    #undef DEF_CMD
    #undef DESTRUCT_ALL_BUFFERS
}