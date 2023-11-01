#include <stdio.h>
#include <stdlib.h>

#include "DisasmErrors.h"
#include "Disassembling.h"
#include "DisasmRead.h"
#include "DisassemblerUtils.h"

int main(int argc, char* argv[])
{
    #define RETURN(error) do{                                               \
        if (disassembler_dtor(&disasmCase))                                 \
        {                                                                   \
            return DTOR_ERROR;                                              \
        }                                                                   \
        return error;                                                       \
    }while(0)

    char* filename = NULL;
    disassemblerErrorCode error = NO_DISASSEMBLER_ERRORS;
    disassemblerCase disasmCase = {};

    if ((error = filename_getter(argc, argv, &filename)))
    {
        print_disassembler_error(stderr, error, 0);

        return 0;
    }

    if ((error = prepare(filename, &disasmCase)))
    {
        print_disassembler_error(stderr, error, 0);
        
        RETURN(0);
    }

    if ((error = disassembling(&disasmCase)))
    {
        print_disassembler_error(stderr, error, disasmCase.IP);
        
        RETURN(0);
    }

    RETURN(0);
    #undef RETURN
}