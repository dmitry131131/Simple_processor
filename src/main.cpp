#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"

int main(int argc, char* argv[])
{   
    processorErrorCode error = NO_PROCESSOR_ERRORS;
    softProcessorUnit processor = {};

    char* filename = NULL;

    if ((error = filename_getter(argc, argv, &filename)))
    {
        print_processor_error(stderr, error);
        return 0;
    }

    if ((error = prepare(filename, &processor)))
    {
        print_processor_error(stderr, error);
        return 0;
    }

    if ((error = processing(&processor)))
    {
        print_processor_error(stderr, error);
        return 0;
    }

    
    return 0;
}
