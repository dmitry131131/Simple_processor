#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"

int main(int argc, char* argv[])
{   
    #define RETURN(error) do{               \
        if (processor_dtor(&processor))     \
        {                                   \
            return DTOR_ERROR;              \
        }                                   \
        return error;                       \
    }while(0)

    processorErrorCode error = NO_PROCESSOR_ERRORS;
    softProcessorUnit processor = {};

    char* filename = NULL;


    if ((error = filename_getter(argc, argv, &filename)))
    {
        print_processor_error(stderr, error, 0);

        RETURN(0);
    }

    if ((error = prepare(filename, &processor)))
    {
        print_processor_error(stderr, error, 0);
        
        RETURN(0);
    }

    if ((error = processing(&processor)))
    {
        print_processor_error(stderr, error, processor.IP);
        processor_dump(&processor, FULL_DUMP);
        
        RETURN(0);
    }

    RETURN(0);
}

#undef RETURN
