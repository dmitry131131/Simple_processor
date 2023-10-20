/**
 * @file
 * @brief Color console output functions source
*/
#include "Color_output.h"

void color_printf(enum consoleColor color, enum consoleStyle style, const char* text, ...)
{
    va_list arguments;
    va_start(arguments, text);
    set_color(stdout, color, style);
    vprintf(text, arguments);
    set_color(stdout, COLOR_DEFAULT, STYLE_NORMAL);
}

void color_fprintf(FILE* stream, enum consoleColor color, enum consoleStyle style, const char* text, ...)
{
    va_list arguments;
    va_start(arguments, text);

    set_color(stream, color, style);
    vfprintf(stream, text, arguments);
    set_color(stream, COLOR_DEFAULT, STYLE_NORMAL);
}

void set_color(FILE* stream, enum consoleColor color, enum consoleStyle style)
{
    fprintf(stream, "\33[%d;3%dm", style, color);
}

void color_putc(FILE* stream, enum consoleColor color, enum consoleStyle style, char ch)
{
    set_color(stream, color, style);
    putc(ch, stream);
    set_color(stream, COLOR_DEFAULT, STYLE_NORMAL);
}

void color_fputs(FILE* stream, enum consoleColor color, enum consoleStyle style, const char* text)
{
    set_color(stream, color, style);
    fputs(text, stream);
    set_color(stream, COLOR_DEFAULT, STYLE_NORMAL);
}