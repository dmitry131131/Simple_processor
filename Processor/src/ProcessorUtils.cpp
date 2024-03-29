#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Error.h"
#include "Stack.h"
#include "Processing.h"
#include "ProcessorUtils.h"  
#include "Color_output.h"

processorErrorCode processor_verify(softProcessorUnit* processor)
{
    assert(processor);
    
    if ((STACK_VERIFY(&(processor->stack))) || (STACK_VERIFY(&(processor->retStack))))
    {
        return VERIFY_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_ctor(softProcessorUnit* processor)
{
    assert(processor);

    processor->stack                = {};
    processor->retStack             = {};
    processor->IP                   = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;
    processor->commandCount         = 0;
    processor->CS                   = NULL;

    processor->RAM                  = (int*) calloc(MEMORY_SIZE, sizeof(int));

    STACK_CTOR(&(processor->stack),    STACK_SIZE);
    STACK_CTOR(&(processor->retStack), RET_STACK_SIZE);

    if (processor->stack.stackErrors || processor->retStack.stackErrors)
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
    assert(processor);

    processor->IP = 0;
    processor->rax = processor->rbx = processor->rcx = processor->rdx = 0;
    processor->commandCount = 0;

    free(processor->CS);
    free(processor->RAM);

    STACK_DTOR(&(processor->stack));
    STACK_DTOR(&(processor->retStack));

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_dump(softProcessorUnit* processor, dumpMode mode)
{
    assert(processor);

    if (processor_verify(processor))
    {
        return NULL_POINTER;
    }

    switch (mode)
    {
    case FULL:
        if (write_register_values(processor)) return NULL_POINTER;
        if (processor_CS_dump(processor)) return NULL_POINTER;

        STACK_DUMP(&(processor->stack), SHORT);
        color_fprintf(stdout, COLOR_GREEN, STYLE_BOLD, "RETURN ADRESS STACK---------------------->\n");
        STACK_DUMP(&(processor->retStack), SHORT);
        break;

    case STACK_ONLY:
        STACK_DUMP(&(processor->stack), SHORT);
        break;

    case RET_STACK_ONLY:
        STACK_DUMP(&(processor->retStack), SHORT);
        break;

    case CS_ONLY:
        if (processor_CS_dump(processor)) return NULL_POINTER;
        break;
    
    case REGISTERS_ONLY:
        if (write_register_values(processor)) return NULL_POINTER;
        break;

    default:
        break;
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode write_register_values(softProcessorUnit* processor)
{
    assert(processor);

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
    assert(processor);

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
    assert(processor);

    size_t start = 0;

    (processor->IP > COUNT_OF_DUMP_COMMANDS) ? (start = processor->IP - COUNT_OF_DUMP_COMMANDS) : start = 0;

    for (size_t i = 0; i < processor->IP - start; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ^\n");

    for (size_t i = 0; i < processor->IP - start; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ip=%lu\n\n", processor->IP);

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode dump_CS_info(const softProcessorUnit* processor, size_t bufferLen)
{
    assert(processor);

    size_t start = 0;
    size_t end   = 0;

    (processor->IP > COUNT_OF_DUMP_COMMANDS) ? (start = processor->IP - COUNT_OF_DUMP_COMMANDS) : start = 0;
    (bufferLen - processor->IP > COUNT_OF_DUMP_COMMANDS) ? (end = processor->IP + COUNT_OF_DUMP_COMMANDS) : end = bufferLen; 

    for (size_t i = start; i < end; i++)
    {
        color_printf(COLOR_YELLOW, STYLE_BLINKING,"%4lu", i);
    }
    putchar('\n');

    size_t colorCounter = 0;
    for (size_t i = start; i < end; i++)
    {
        if (colorCounter)
        {
            printf("%4d", processor->CS[i]);
            colorCounter--;
            continue;
        } 
        else if (processor->CS[i] == (PUSH | IMM))
        {
            colorCounter = sizeof(double);
        }
        else if (processor->CS[i] == JMP || processor->CS[i] == JA  || processor->CS[i] == JAE
            ||   processor->CS[i] == JB  || processor->CS[i] == JBE || processor->CS[i] == JE
            ||   processor->CS[i] == JNE || processor->CS[i] == CALL
            ||   ((unsigned int) processor->CS[i] & COMMAND_MASK) == (PUSH | RAM | IMM)
            ||   ((unsigned int) processor->CS[i] & COMMAND_MASK) == (POP  | RAM | IMM))
        {
            colorCounter = sizeof(int);
        }
        else if (((unsigned int) processor->CS[i] & COMMAND_MASK) == (PUSH | RAM | IMM | REG)
            ||   ((unsigned int) processor->CS[i] & COMMAND_MASK) == (POP  | RAM | IMM | REG))
        {
            colorCounter = sizeof(char) + sizeof(int);
        }
        else if (processor->CS[i] == (PUSH | REG) || processor->CS[i] == (POP | REG))
        {
            colorCounter = sizeof(char);
        }
        
        color_printf(COLOR_CYAN, STYLE_BOLD,"%4u", (unsigned int) processor->CS[i] & COMMAND_MASK);
    }
    putchar('\n');

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode count_len_of_buffer(const softProcessorUnit* processor, size_t* bufferLen)
{
    assert(processor);
    assert(bufferLen);

    for (size_t i = 0; i < processor->commandCount; i++)
    {
        if ((int) processor->CS[*bufferLen] == (PUSH | IMM))
        {
            (*bufferLen) += (sizeof(char) + sizeof(double));
        }

        else if ((int) processor->CS[*bufferLen] == JMP || (int) processor->CS[*bufferLen] == JA
            ||   (int) processor->CS[*bufferLen] == JAE || (int) processor->CS[*bufferLen] == JB
            ||   (int) processor->CS[*bufferLen] == JBE || (int) processor->CS[*bufferLen] == JE
            ||   (int) processor->CS[*bufferLen] == JNE || (int) processor->CS[*bufferLen] == CALL
            ||   ((unsigned int) processor->CS[*bufferLen] & COMMAND_MASK) == (PUSH | RAM | IMM)
            ||   ((unsigned int) processor->CS[*bufferLen] & COMMAND_MASK) == (POP  | RAM | IMM))
        {
            (*bufferLen) += (sizeof(char) + sizeof(int));
        }

        else if (((unsigned int) processor->CS[*bufferLen] & COMMAND_MASK) == (PUSH | RAM | IMM | REG)
            ||   ((unsigned int) processor->CS[*bufferLen] & COMMAND_MASK) == (POP  | RAM | IMM | REG))
        {
            (*bufferLen) += (2*sizeof(char) + sizeof(int));
        }

        else if ((int) processor->CS[*bufferLen] == (PUSH | REG) || (int) processor->CS[*bufferLen] == (POP | REG))
        {
            (*bufferLen) += (2 * sizeof(char));
        }

        else
        {
            (*bufferLen) += sizeof(char);
        }
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len)
{
    assert(buffer);
    assert(ptr);

    for (size_t i = 0; i < len; i++)
    {
        *((char*) ptr + i) = buffer[i];
    }

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode calculate_RAM_adress(softProcessorUnit* processor, registerNames reg, int* adress)
{
    assert(processor);
    assert(adress);
    assert(adress);

    switch (reg)
    {
    case RAX:
        *adress += processor->rax;
        break;

    case RBX:
        *adress += processor->rbx;
    break;

    case RCX:
        *adress += processor->rcx;
    break;
    
    case RDX:
        *adress += processor->rdx;
    break;

    case RPX:
        *adress += processor->rpx;
    break;

    case NO_REG:
        return WRONG_COMMAND;
        break;
    default:
        return WRONG_COMMAND;
        break;
    }

    return NO_PROCESSOR_ERRORS;
}