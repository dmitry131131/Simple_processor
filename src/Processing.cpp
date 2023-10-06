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

enum processorErrorCode processing(textData* text)
{
    Stack stack = {};
    STACK_CTOR(&stack, 10);

    if (stack.stackErrors)
    {
        abort();
        return CTOR_ERROR;
    }

    int comandCode = 0;

    for (size_t i = 0; i < text->linesCount; i++)
    {
        comandCode = 0;
        if (sscanf(text->linesPtr[i], "%d", &comandCode) != 1)
        {
            print_processor_error(stderr, WRONG_COMMAND, i+1, text->linesPtr[i]);
            STACK_DTOR(&stack);
            return WRONG_COMMAND;
        }

        processorErrorCode err = NO_PROCESSOR_ERRORS;

        switch (comandCode)
        {
        case 1:
            err = processor_push(text->linesPtr[i], &stack);
            break;

        case 2:
            err = processor_add(&stack);
            break;

        case 3:
            err = processor_sub(&stack);
            break;

        case 4:
            err = processor_mue(&stack);
            break;

        case 5:
            err = processor_div(&stack);
            break;

        case 6:
            err = processor_out(&stack, stdout);
            break;

        case 7:
            err = processor_sqrt(&stack);
            break;

        case 8:
        case 9:
        case 10:
            err = processor_trig(&stack, comandCode);
            break;

        case 11:
            err = processor_in(&stack, stdin);
            break;

        case 12:
            err = processor_hlt(&stack);
            return NO_PROCESSOR_ERRORS;
            break;

        default:
            print_processor_error(stderr, WRONG_COMMAND, i+1, text->linesPtr[i]);
            STACK_DTOR(&stack);
            return WRONG_COMMAND;
            break;
        }

        if (err)
        {
            print_processor_error(stderr, err, i+1, text->linesPtr[i]);
            STACK_DTOR(&stack);
            return err;
        }
    }

    STACK_DTOR(&stack);

    return NO_PROCESSOR_ERRORS;
}

enum processorErrorCode processor_push(const char* line, Stack* stack)
{
    double num = NAN;
    int code = 0, intNum = 0;
    if (sscanf(line, "%d %lf", &code, &num) != 2)
    {
        return WRONG_NUMBER;
    }

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

enum processorErrorCode processor_mue(Stack* stack)
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

enum processorErrorCode processor_trig(Stack* stack, int mode)
{
    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        return POP_ERROR;
    }

    int root = 0;
    switch (mode)
    {
    case 8:
        root = (int) (sin(((double) num) / DOUBLE_COEF) * DOUBLE_COEF);
        break;

    case 9:
        root = (int) (cos(((double) num) / DOUBLE_COEF) * DOUBLE_COEF);
        break;
    
    case 10:
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
    STACK_DTOR(stack);

    return NO_PROCESSOR_ERRORS;
}