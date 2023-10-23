#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "ProcessorUtils.h"  
#include "Color_output.h"

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

processorErrorCode processor_dump(softProcessorUnit* processor, dumpMode mode)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    if (processor_verify(processor))
    {
        return NULL_POINTER;
    }

    if (mode != STACK_ONLY)
    {
        if (write_register_values(processor)) return NULL_POINTER;
        if (processor_CS_dump(processor)) return NULL_POINTER;
    }
    if (mode != WITHOUT_STACK)
    {
        STACK_DUMP(&(processor->stack));
    }
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode write_register_values(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    color_printf(COLOR_RED, STYLE_BOLD, "REGISTERS:\n");

    color_printf(COLOR_PURPLE, STYLE_BOLD, "RAX = ");
    printf("%d\n", processor->rax);
    color_printf(COLOR_PURPLE, STYLE_BOLD, "RBX = ");
    printf("%d\n", processor->rbx);
    color_printf(COLOR_PURPLE, STYLE_BOLD, "RCX = ");
    printf("%d\n", processor->rcx);
    color_printf(COLOR_PURPLE, STYLE_BOLD, "RDX = ");
    printf("%d\n", processor->rdx);
    putchar('\n');
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

    color_printf(COLOR_RED, STYLE_BOLD, "CS:\n");

    size_t bufferLen = 0;

    if (count_len_of_buffer(processor, &bufferLen))
    {
        return NULL_POINTER;
    }

    if (dump_CS_info(processor, bufferLen))
    {
        return NULL_POINTER;
    }
    
    if (write_CS_bird(processor))
    {
        return NULL_POINTER;
    }
    
    return NO_PROCESSOR_ERRORS;
}

processorErrorCode write_CS_bird(softProcessorUnit* processor)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    for (size_t i = 0; i < processor->IP; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ^\n");

    for (size_t i = 0; i < processor->IP; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ip=%lu\n\n", processor->IP);

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode dump_CS_info(const softProcessorUnit* processor, size_t bufferLen)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

    for (size_t i = 0; i < bufferLen; i++)
    {
        color_printf(COLOR_YELLOW, STYLE_BLINKING,"%4lu", i);
    }
    putchar('\n');

    size_t colorCounter = 0;
    for (size_t i = 0; i < bufferLen; i++)
    {
        if (colorCounter)
        {
            printf("%4d", processor->CS[i]);
            colorCounter--;
            continue;
        } 
        else if (processor->CS[i] == (PUSH | IMM))
        {
            colorCounter = 8;
        }
        else if (processor->CS[i] == JMP || processor->CS[i] == JA  || processor->CS[i] == JAE
            ||   processor->CS[i] == JB  || processor->CS[i] == JBE || processor->CS[i] == JE
            ||   processor->CS[i] == JNE)
        {
            colorCounter = 4;
        }
        else if (processor->CS[i] == (PUSH | REG) || processor->CS[i] == (POP | REG))
        {
            colorCounter = 1;
        }
        
        color_printf(COLOR_CYAN, STYLE_BOLD,"%4d", processor->CS[i]);
    }
    putchar('\n');

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode count_len_of_buffer(const softProcessorUnit* processor, size_t* bufferLen)
{
    if (!processor)
    {
        return NULL_POINTER;
    }
    if (!bufferLen)
    {
        return NULL_POINTER;
    }

    for (size_t i = 0; i < processor->commandCount; i++)
    {
        if ((int) processor->CS[*bufferLen] == (PUSH | IMM))
        {
            (*bufferLen) += 9;
        }

        else if ((int) processor->CS[*bufferLen] == JMP || (int) processor->CS[*bufferLen] == JA
            ||   (int) processor->CS[*bufferLen] == JAE || (int) processor->CS[*bufferLen] == JB
            ||   (int) processor->CS[*bufferLen] == JBE || (int) processor->CS[*bufferLen] == JE
            ||   (int) processor->CS[*bufferLen] == JNE)
        {
            (*bufferLen) += 5;
        }

        else if ((int) processor->CS[*bufferLen] == (PUSH | REG) || (int) processor->CS[*bufferLen] == (POP | REG))
        {
            (*bufferLen) += 2;
        }

        else
        {
            (*bufferLen)++;
        }
    }

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