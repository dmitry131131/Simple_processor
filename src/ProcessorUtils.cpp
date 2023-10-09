#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "ProcessorUtils.h"  

processorErrorCode processor_verify(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }
    
    if (STACK_VERIFY(&(processor->stack)))
    {
        return VERIFY_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_ctor(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    processor->stack = {};
    processor->IP = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;
    processor->commandCount = 0;
    processor->CS = NULL; //(int*) calloc(commandCount + 1, sizeof(int));

    STACK_CTOR(&(processor->stack), 10);

    if (processor->stack.stackErrors)
    {
        return STACK_CTOR_ERROR;
    }

    if (processor_verify(processor))
    {
        return VERIFY_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_dtor(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    if (processor_verify(processor))
    {
        return VERIFY_ERROR;
    }

    processor->IP = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;
    processor->commandCount = 0;

    free(processor->CS);

    STACK_DTOR(&(processor->stack));

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_dump(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    if (processor_verify(processor))
    {
        return NULL_POINTER;
    }

    STACK_DUMP(&(processor->stack));

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_CS_dump(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    if (!(processor->CS))
    {
        return NULL_POINTER;
    }

    size_t bufferLen = 0;

    for (size_t i = 0; i < processor->commandCount; i++)
    {
        if ((int) processor->CS[bufferLen] == 17)
        {
            bufferLen += 9;
        }

        else if ((int) processor->CS[bufferLen] == 33 || (int) processor->CS[bufferLen] == 11)
        {
            bufferLen += 2;
        }

        else
        {
            bufferLen++;
        }
    }

    for (size_t i = 0; i < bufferLen; i++)
    {
        printf("%4lu", i);
    }
    putchar('\n');

    size_t bufferPos = 0;

    for (size_t i = 0; i < bufferLen; i++)
    {
        printf("%4d", processor->CS[i]);
    }

    putchar('\n');

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len)
{
    if (!buffer)
    {
        return NULL_POINTER;
    }
    if (!ptr)
    {
        return NULL_POINTER;
    }

    for (size_t i = 0; i < len; i++)
    {
        *((char*) ptr + i) = buffer[i];
    }

    return NO_PROCESSOR_ERRORS;
}