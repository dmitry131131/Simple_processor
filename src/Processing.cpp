/**
 * @file 
 * @brief Processing functions sources
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Stack.h"
#include "InputOutput.h"
#include "Processing.h"
#include "MathUtils.h"

enum errorCode processing(textData* text)
{
    Stack stack = {};
    STACK_CTOR(&stack, 10);

    if (stack.stackErrors)
    {
        abort();
        return stack.stackErrors;
    }

    int comandCode = 0;

    for (size_t i = 0; i < text->linesCount; i++)
    {
        comandCode = 0;
        if (sscanf(text->linesPtr[i], "%d", &comandCode) != 1)
        {
            printf("command error!\n");
            // Wrong comand
        }
        switch (comandCode)
        {
        case 1:
            processor_push(text->linesPtr[i], &stack);
            break;

        case 2:
            processor_add(&stack);
            break;

        case 3:
            processor_sub(&stack);
            break;

        case 4:
            processor_mue(&stack);
            break;

        case 5:
            processor_div(&stack);
            break;

        case 6:
            processor_out(&stack, stdout);
            break;

        case 7:
            processor_sqrt(&stack);
            break;

        case 8:
            processor_trig(&stack, 8);
            break;

        case 9:
            processor_trig(&stack, 9);
            break;

        case 10:
            processor_trig(&stack, 10);
            break;

        case 11:
            processor_in(&stack, stdin);
            break;

        case 12:
            processor_hlt(&stack);
            return NO_ERRORS;
            break;
        
        default:
            // Wrong comand
            break;
        }
    }

    STACK_DTOR(&stack);

    return NO_ERRORS;
}

enum errorCode processor_push(const char* line, Stack* stack)
{
    double num = NAN;
    int code = 0, intNum = 0;
    if (sscanf(line, "%d %lf", &code, &num) != 1)
    {
        // Wrong comand
    }

    intNum = (int) (num * DOUBLE_COEF);

    if (STACK_PUSH(stack, intNum))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_add(Stack* stack)
{
    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        // pop error
    }

    if (STACK_PUSH(stack, (intNum1 + intNum2)))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_sub(Stack* stack)
{
    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        // pop error
    }

    if (STACK_PUSH(stack, intNum1 - intNum2))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_mue(Stack* stack)
{
    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        // pop error
    }

    if (STACK_PUSH(stack, (intNum1 * intNum2 / DOUBLE_COEF)))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_div(Stack* stack)
{
    int intNum2 = STACK_POP(stack);
    int intNum1 = STACK_POP(stack);

    if (intNum1 == ELEM_T_POISON || intNum2 == ELEM_T_POISON) 
    {
        // pop error
    }

    if (STACK_PUSH(stack, ((int) (((double) intNum1 / intNum2) * DOUBLE_COEF))))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_out(Stack* stack, FILE* stream)
{
    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        // pop error
        return stack->stackErrors;
    }

    fprintf(stream, "%.4lf\n", (double) num / DOUBLE_COEF);

    return NO_ERRORS;
}

enum errorCode processor_sqrt(Stack* stack)
{
    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        // pop error
        return stack->stackErrors;
    }

    if (STACK_PUSH(stack, (int) (sqrt((float) (num / DOUBLE_COEF)) * DOUBLE_COEF)))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_trig(Stack* stack, int mode)
{
    int num = STACK_POP(stack);

    if (num == ELEM_T_POISON)
    {
        // pop error
        return stack->stackErrors;
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
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_in(Stack* stack, FILE* inputStream)
{ 
    double num = NAN;

    if (fscanf(inputStream, "%lf", &num) != 1)
    {
        // input error
    }

    int intNum = (int) (num * DOUBLE_COEF);

    if (STACK_PUSH(stack, intNum))
    {
        // push error
        return stack->stackErrors;
    }

    return NO_ERRORS;
}

enum errorCode processor_hlt(Stack* stack)
{
    STACK_DTOR(stack);

    return NO_ERRORS;
}