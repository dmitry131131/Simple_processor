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
    double num = NAN;
    double num1 = NAN, num2 = NAN;

    for (size_t i = 0; i < text->linesCount; i++)
    {
        comandCode = 0;

        if (sscanf(text->linesPtr[i], "%d", &comandCode) != 1)
        {
            // Wrong comand
        }
        switch (comandCode)
        {
        case 1:
            num = NAN;
            if (sscanf(text->linesPtr[i], "%lf", &num) != 1)
            {
                // Wrong comand
            }
            if (STACK_PUSH(&stack, num))
            {
                // push error
                return stack.stackErrors;
            }

            break;

        case 2:
            num1 = NAN;
            num2 = NAN;
            num2 = STACK_POP(&stack);
            num1 = STACK_POP(&stack);

            if (isnan(num1) || isnan(num2)) 
            {
                // invalid num
                break;
            }

            if (EqualityNumbers(num2, 0))
            {
                //devision by zero
                break;
            }

            if (STACK_PUSH(&stack, num1 / num2))
            {
                // push error
                return stack.stackErrors;
            }

            break;
        
        default:
            // Wrong comand
            break;
        }
    }

    return NO_ERRORS;
}