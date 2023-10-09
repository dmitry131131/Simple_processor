#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "Read.h"
#include "ProcessorUtils.h"

int main()
{
    softProcessorUnit processor = {};

    if (prepare("outbin", &processor))
    {
        return 0;
    }

    processor_dump(&processor);

    if (processing(&processor))
    {
        return 0;
    }

    
    return 0;
}
