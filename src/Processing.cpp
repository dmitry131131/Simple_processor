/**
 * @file 
 * @brief Processing functions sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Error.h"
#include "Stack.h"
#include "InputOutput.h"
#include "Processing.h"
#include "ProcessorUtils.h"

enum processorErrorCode processing(softProcessorUnit* processor)
{
    commandCodes command = NO_COMMAND;
    double commandArg = NAN;

    registerNames reg = NO_REG;
    processorErrorCode err = NO_PROCESSOR_ERRORS;
    for (size_t commNum = 0; commNum < processor->commandCount; commNum++)
    {
        processor_dump(processor, WITHOUT_STACK);
        command = (commandCodes) *(processor->CS + processor->IP);
        switch ((int) command)
        {
        case (PUSH | 1 << 4):
            processor->IP++;
            if (copy_data_from_buffer(processor->CS + processor->IP, &commandArg, 8))
            {
                return COPU_ARG_ERROR;
            }

            err = processor_push(commandArg, &(processor->stack));

            processor->IP += 8;
            break;

        case (PUSH | 1 << 5):
            processor->IP++;

            reg = (registerNames) *(processor->CS + processor->IP);

            err = processor_push_from_register(processor, reg);

            processor->IP++;
            break;

        case (POP | 1 << 5):
            processor->IP++;

            reg = (registerNames) *(processor->CS + processor->IP);

            err = processor_pop(processor, reg);

            processor->IP++;

            break;

        case IN:
            err = processor_in(&(processor->stack));
            processor->IP++;
            break;
        
        case ADD:
            err = processor_add(&(processor->stack));
            processor->IP++;
            break;

        case SUB:
            err = processor_sub(&(processor->stack));
            processor->IP++;
            break;

        case MUL:
            err = processor_mul(&(processor->stack));
            processor->IP++;
            break;

        case DIV:
            err = processor_div(&(processor->stack));
            processor->IP++;
            break;

        case OUT:
            err = processor_out(&(processor->stack), stdout);
            processor->IP++;
            break;

        case SQRT:
            err = processor_sqrt(&(processor->stack));
            processor->IP++;
            break;

        case SIN:

        case COS:

        case TAN:
            err = processor_trig(&(processor->stack), command);
            processor->IP++;
            break;

        case HLT:
            err = processor_hlt(&(processor->stack));
            processor->IP++;
            break;
        
        default:
            break;
        }
    }

    if (processor_dtor(processor))
    {
        return DTOR_ERROR;
    }

    if (err) return err;

    return NO_PROCESSOR_ERRORS;
}

processorErrorCode processor_pop(softProcessorUnit* processor, registerNames reg)
{
    if (!processor)
    {
        return NULL_POINTER;
    }

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
    if (!processor)
    {
        return NULL_POINTER;
    }

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
    if (!stack)
    {
        return NULL_POINTER;
    }

    int intNum = (int) (num * DOUBLE_COEF);

    if (STACK_PUSH(stack, intNum))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_add(Stack* stack)
{
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
    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        return POP_ERROR;
    }

    if (STACK_PUSH(stack, (int) (sqrt((float) (num / DOUBLE_COEF)) * DOUBLE_COEF)))
    {
        return PUSH_ERROR;
    }

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_trig(Stack* stack, commandCodes mode)
{
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
    if (!stack)
    {
        return NULL_POINTER;
    }

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

    return NO_PROCESSOR_ERRORS;
}