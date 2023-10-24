/**
 * @file 
 * @brief Processing functions sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "Error.h"
#include "Stack.h"
#include "InputOutput.h"
#include "Processing.h"
#include "ProcessorUtils.h"

enum processorErrorCode processing(softProcessorUnit* processor)
{

    #define RETURN(error) do{               \
        if (processor_dtor(processor))      \
        {                                   \
            return DTOR_ERROR;              \
        }                                   \
        return error;                       \
    }while(0)

    #define DEF_CMD(name, num, arg, asm_code, proc_code)    \
        case num:                                           \
            proc_code                                       \
            break;                                          

    commandCodes command = NO_COMMAND;
    double commandArg = NAN;

    registerNames reg = NO_REG;
    processorErrorCode err = NO_PROCESSOR_ERRORS;
    for (size_t commNum = 0; commNum < processor->commandCount; commNum++)
    {
        processor_dump(processor, FULL_DUMP);
        command = (commandCodes) *(processor->CS + processor->IP);

        switch (command & COMMAND_PART)
        {
        
        #include "Functions.def"
        
        default:
            err = WRONG_COMMAND;
            break;
        }
    }

    if (err)
    {
        RETURN(err);
    }

    if (processor_dtor(processor))
    {
        RETURN(DTOR_ERROR);
    }

    #undef RETURN

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_jmp(softProcessorUnit* processor, int ip)
{
    assert(processor);

    if (ip < 0)
    {
        return BAD_IP;
    }

    processor->IP = (size_t) ip;

    return NO_PROCESSOR_ERRORS;
}

#define JUMP_PATTERN(sign) do{                                              \
        assert(processor);                                                  \
                                                                            \
        if (ip < 0)                                                         \
        {                                                                   \
            return BAD_IP;                                                  \
        }                                                                   \
                                                                            \
        int first_num  = STACK_POP(&(processor->stack));                    \
        int second_num = STACK_POP(&(processor->stack));                    \
                                                                            \
        if (first_num == ELEM_T_POISON || second_num == ELEM_T_POISON)      \
        {                                                                   \
            return POP_ERROR;                                               \
        }                                                                   \
                                                                            \
        processorErrorCode error = NO_PROCESSOR_ERRORS;                     \
        if (first_num sign second_num)                                      \
        {                                                                   \
            error = processor_jmp(processor, ip);                           \
        }                                                                   \
        else                                                                \
        {                                                                   \
            processor->IP += sizeof(int);                                   \
        }                                                                   \
                                                                            \
        return error;                                                       \
    }while(0)                        

processorErrorCode processor_ja(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(<);
}

processorErrorCode processor_jae(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(<=);
}

processorErrorCode processor_jb(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(>);
}

processorErrorCode processor_jbe(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(>=);
}

processorErrorCode processor_je(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(==);
}

processorErrorCode processor_jne(softProcessorUnit* processor, int ip)
{
    JUMP_PATTERN(!=);
}

#undef JUMP_PATTERN

processorErrorCode processor_pop(softProcessorUnit* processor, registerNames reg)
{
    assert(processor);

    int data = STACK_POP(&(processor->stack));
    
    switch (reg)
    {
    case RAX:
        processor->rax = data;
        break;

    case RBX:
        processor->rbx = data;
    break;

    case RCX:
        processor->rcx = data;
    break;
    
    case RDX:
        processor->rdx = data;
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

processorErrorCode processor_push_from_register(softProcessorUnit* processor, registerNames reg)
{
    assert(processor);

    int data = 0;
    switch (reg)
    {
    case RAX:
        data = processor->rax;
        break;

    case RBX:
        data = processor->rbx;
    break;

    case RCX:
        data = processor->rcx;
    break;
    
    case RDX:
        data = processor->rdx;
    break;

    case NO_REG:
        return WRONG_COMMAND;
    break;
    default:
        return WRONG_COMMAND;
        break;
    }

    if (STACK_PUSH(&(processor->stack), data))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_push(double num, Stack* stack)
{
    assert(stack);

    int intNum = (int) (num * DOUBLE_COEF);

    if (STACK_PUSH(stack, intNum))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_add(Stack* stack)
{
    assert(stack);

    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        return POP_ERROR;
    }

    if (STACK_PUSH(stack, (intNum1 + intNum2)))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_sub(Stack* stack)
{
    assert(stack);

    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        return POP_ERROR;
    }

    if (STACK_PUSH(stack, intNum1 - intNum2))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_mul(Stack* stack)
{
    assert(stack);

    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        return POP_ERROR;
    }

    if (STACK_PUSH(stack, (intNum1 * intNum2 / DOUBLE_COEF)))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_div(Stack* stack)
{
    assert(stack);

    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        return POP_ERROR;
    }

    if (intNum2 == 0)
    {
        return DIVIDION_BY_ZERO;
    }

    if (STACK_PUSH(stack, ((int) (((double) intNum1 / intNum2) * DOUBLE_COEF))))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_out(Stack* stack, FILE* stream)
{
    assert(stack);

    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        return POP_ERROR;
    }

    fprintf(stream, "%.4lf\n", (double) num / DOUBLE_COEF);

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_sqrt(Stack* stack)
{
    assert(stack);

    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        return POP_ERROR;
    }

    if (STACK_PUSH(stack, (int) (sqrt((double) (num / DOUBLE_COEF)) * DOUBLE_COEF)))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_trig(Stack* stack, commandCodes mode)
{
    assert(stack);

    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        return POP_ERROR;
    }

    int root = 0;
    switch ((int) mode)
    {
    case SIN:
        root = (int) (sin(((double) num) / DOUBLE_COEF) * DOUBLE_COEF);
        break;

    case COS:
        root = (int) (cos(((double) num) / DOUBLE_COEF) * DOUBLE_COEF);
        break;
    
    case TAN:
        root = (int) (tan(((double) num) / DOUBLE_COEF) * DOUBLE_COEF);
        break;
    
    default:
        break;
    }

    if (STACK_PUSH(stack, root))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_in(Stack* stack)
{ 
    assert(stack);

    double num = NAN;

    if (scanf("%lf", &num) != 1)
    {
        return WRONG_NUMBER;
    }

    int intNum = (int) (num * DOUBLE_COEF);

    if (STACK_PUSH(stack, intNum))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_hlt(Stack* stack)
{
    assert(stack);
    
    return NO_PROCESSOR_ERRORS;
}