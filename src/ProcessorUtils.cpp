#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Processing.h"
#include "Stack.h"
#include "ProcessorUtils.h"  

processorErrorCode processor_verify(softProcessorUnit* processor)
{
    if (!processor)
    {
        // nullptr error
    }

    if (!(processor->CS))
    {
        // CS nullptr
    }

    if (STACK_VERIFY(&(processor->stack)))
    {
        // Stack error
    }

    return ;
}

processorErrorCode processor_ctor(softProcessorUnit* processor, size_t commandCount)
{
    if (!processor)
    {
        // nullptr error
    }

    if (processor_verify(processor))
    {
        // verify error
    }

    processor->stack = {};
    processor->IP = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;
    processor->CS = (int*) calloc(commandCount, sizeof(int));

    if (!(processor->CS))
    {
        // calloc error
    }

    STACK_CTOR(&(processor->stack), 10);

    if (processor->stack.stackErrors)
    {
        // stack ctor error
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_dtor(softProcessorUnit* processor)
{
    if (!processor)
    {
        // nullptr error
    }

    if (processor_verify(processor))
    {
        // verify error
    }

    processor->IP = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;

    free(processor->CS);

    STACK_DTOR(&(processor->stack));

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_dump(softProcessorUnit* processor)
{
    if (!processor)
    {
        // nullptr error
    }

    if (processor_verify(processor))
    {
        // verify error
    }

    STACK_DUMP(&(processor->stack));

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_CS_dump(softProcessorUnit* processor)
{
    if (!processor)
    {
        // nullptr error
    }

    if (processor_verify(processor))
    {
        // verify error
    }

    


    return NO_PROCESSOR_ERRORS;
}