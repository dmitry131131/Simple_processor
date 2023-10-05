/**
 * @file
 * @brief Functions working with processor errors sources
*/
#include <stdio.h>

#include "Error.h"
#include "Color_output.h"

void print_processor_error(FILE* stream, processorErrorCode error, size_t line, const char* text)
{
    print_processor_error_message(stream, error);

    color_fprintf(stream, COLOR_CYAN, STYLE_BOLD, "In line: ");
    fprintf(stream, "%lu ", line);
    color_fprintf(stream, COLOR_PURPLE, STYLE_BOLD, "Command: ");
    color_fprintf(stream, COLOR_DEFAULT, STYLE_INVERT_C, "%s\n", text);
}

void print_processor_error_message(FILE* stream, processorErrorCode error)
{
    color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");

    switch (error)
    {
    case NO_PROCESSOR_ERRORS:
        break;
    
    case WRONG_COMMAND:
        fprintf(stream, "Unknown command entered!\n");
        break;

    case WRONG_NUMBER:
        fprintf(stream, "Wrong number entered!\n");
        break;

    case CTOR_ERROR:
        fprintf(stream, "Stack constructor error!\n");
        break;

    case PUSH_ERROR:
        fprintf(stream, "Push in stack error!\n");
        break;

    case POP_ERROR:
        fprintf(stream, "Pop from stack error!\n");
        break;

    case DIVIDION_BY_ZERO:
        fprintf(stream, "Dividion by zero!\n");
        break;

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }
}
