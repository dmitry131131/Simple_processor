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
    processorErrorCode err = NO_PROCESSOR_ERRORS;
    for (size_t commNum = 0; commNum < processor->commandCount; commNum++)
    {
        command = (commandCodes) *(processor->CS + processor->IP);
        switch (command)
        {
        case PUSH:
            processor->IP++;
            if (copy_data_from_buffer(processor->CS + processor->IP, &commandArg, 8))
            {
                return COPU_ARG_ERROR;
            }

            err = processor_push(commandArg, &(processor->stack));

            processor->IP += 8;
            break;

        case IN:
            
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

enum processorErrorCode processor_push(double num, Stack* stack)
{
    if (!stack)
    {
        return NULL_POINTER;
    }

    int code = 0, intNum = 0;

    intNum = (int) (num * DOUBLE_COEF);

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
    switch (mode)
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

enum processorErrorCode processor_in(Stack* stack, FILE* inputStream)
{ 
    double num = NAN;

    if (fscanf(inputStream, "%lf", &num) != 1)
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