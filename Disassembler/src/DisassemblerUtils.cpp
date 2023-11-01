#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "DisasmErrors.h"
#include "Disassembling.h"
#include "DisassemblerUtils.h"  
#include "Color_output.h"

disassemblerErrorCode disassembler_verify(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode disassembler_ctor(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    disasmCase->IP                   = 0;
    disasmCase->commandCount         = 0;
    disasmCase->CS                   = NULL;

    if (disassembler_verify(disasmCase))
    {
        return VERIFY_ERROR;
    }

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode disassembler_dtor(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    disasmCase->IP = 0;
    disasmCase->commandCount = 0;

    free(disasmCase->CS);

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode disassembler_dump(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    if (disassembler_verify(disasmCase))
    {
        return VERIFY_ERROR;
    }
    disassemblerErrorCode error = NO_DISASSEMBLER_ERRORS;

    if ((error = processor_CS_dump(disasmCase))) return error;

    return error;
}

disassemblerErrorCode processor_CS_dump(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    if (!(disasmCase->CS))
    {
        return NULL_POINTER;
    }

    color_printf(COLOR_RED, STYLE_BOLD, "CS:\n");

    size_t bufferLen = 0;

    if (count_len_of_buffer(disasmCase, &bufferLen))
    {
        return NULL_POINTER;
    }

    if (dump_CS_info(disasmCase, bufferLen))
    {
        return NULL_POINTER;
    }
    
    if (write_CS_bird(disasmCase))
    {
        return NULL_POINTER;
    }
    
    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode write_CS_bird(disassemblerCase* disasmCase)
{
    assert(disasmCase);

    size_t start = 0;

    (disasmCase->IP > COUNT_OF_DUMP_COMMANDS) ? (start = disasmCase->IP - COUNT_OF_DUMP_COMMANDS) : start = 0;

    for (size_t i = 0; i < disasmCase->IP - start; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ^\n");

    for (size_t i = 0; i < disasmCase->IP - start; i++)
    {
        printf("    ");
    }
    color_printf(COLOR_PURPLE, STYLE_BOLD,"   ip=%lu\n\n", disasmCase->IP);

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode dump_CS_info(const disassemblerCase* disasmCase, size_t bufferLen)
{
    assert(disasmCase);

    size_t start = 0;
    size_t end   = 0;

    (disasmCase->IP > COUNT_OF_DUMP_COMMANDS) ? (start = disasmCase->IP - COUNT_OF_DUMP_COMMANDS) : start = 0;
    (bufferLen - disasmCase->IP > COUNT_OF_DUMP_COMMANDS) ? (end = disasmCase->IP + COUNT_OF_DUMP_COMMANDS) : end = bufferLen; 

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
            printf("%4d", disasmCase->CS[i]);
            colorCounter--;
            continue;
        } 
        else if (disasmCase->CS[i] == (PUSH | IMM))
        {
            colorCounter = sizeof(double);
        }
        else if (disasmCase->CS[i] == JMP || disasmCase->CS[i] == JA  || disasmCase->CS[i] == JAE
            ||   disasmCase->CS[i] == JB  || disasmCase->CS[i] == JBE || disasmCase->CS[i] == JE
            ||   disasmCase->CS[i] == JNE || disasmCase->CS[i] == CALL
            ||   ((unsigned int) disasmCase->CS[i] & COMMAND_MASK) == (PUSH | RAM | IMM)
            ||   ((unsigned int) disasmCase->CS[i] & COMMAND_MASK) == (POP  | RAM | IMM))
        {
            colorCounter = sizeof(int);
        }
        else if (((unsigned int) disasmCase->CS[i] & COMMAND_MASK) == (PUSH | RAM | IMM | REG)
            ||   ((unsigned int) disasmCase->CS[i] & COMMAND_MASK) == (POP  | RAM | IMM | REG))
        {
            colorCounter = sizeof(char) + sizeof(int);
        }
        else if (disasmCase->CS[i] == (PUSH | REG) || disasmCase->CS[i] == (POP | REG))
        {
            colorCounter = sizeof(char);
        }
        
        color_printf(COLOR_CYAN, STYLE_BOLD,"%4u", (unsigned int) disasmCase->CS[i] & COMMAND_MASK);
    }
    putchar('\n');

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode count_len_of_buffer(const disassemblerCase* disasmCase, size_t* bufferLen)
{
    assert(disasmCase);
    assert(bufferLen);

    for (size_t i = 0; i < disasmCase->commandCount; i++)
    {
        if ((int) disasmCase->CS[*bufferLen] == (PUSH | IMM))
        {
            (*bufferLen) += (sizeof(char) + sizeof(double));
        }

        else if ((int) disasmCase->CS[*bufferLen] == JMP || (int) disasmCase->CS[*bufferLen] == JA
            ||   (int) disasmCase->CS[*bufferLen] == JAE || (int) disasmCase->CS[*bufferLen] == JB
            ||   (int) disasmCase->CS[*bufferLen] == JBE || (int) disasmCase->CS[*bufferLen] == JE
            ||   (int) disasmCase->CS[*bufferLen] == JNE || (int) disasmCase->CS[*bufferLen] == CALL
            ||   ((unsigned int) disasmCase->CS[*bufferLen] & COMMAND_MASK) == (PUSH | RAM | IMM)
            ||   ((unsigned int) disasmCase->CS[*bufferLen] & COMMAND_MASK) == (POP  | RAM | IMM))
        {
            (*bufferLen) += (sizeof(char) + sizeof(int));
        }

        else if (((unsigned int) disasmCase->CS[*bufferLen] & COMMAND_MASK) == (PUSH | RAM | IMM | REG)
            ||   ((unsigned int) disasmCase->CS[*bufferLen] & COMMAND_MASK) == (POP  | RAM | IMM | REG))
        {
            (*bufferLen) += (2*sizeof(char) + sizeof(int));
        }

        else if ((int) disasmCase->CS[*bufferLen] == (PUSH | REG) || (int) disasmCase->CS[*bufferLen] == (POP | REG))
        {
            (*bufferLen) += (2 * sizeof(char));
        }

        else
        {
            (*bufferLen) += sizeof(char);
        }
    }

    return NO_DISASSEMBLER_ERRORS;
}

disassemblerErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len)
{
    assert(buffer);
    assert(ptr);

    for (size_t i = 0; i < len; i++)
    {
        *((char*) ptr + i) = buffer[i];
    }

    return NO_DISASSEMBLER_ERRORS;
}