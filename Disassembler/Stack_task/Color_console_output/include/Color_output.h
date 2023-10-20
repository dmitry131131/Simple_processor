/**
 * @file
 * @brief Color console output functions
*/
#ifndef COLOR_CONSOLE
#define COLOR_CONSOLE

#include <stdio.h>
#include <stdarg.h>

/// @brief enum with color variants
enum consoleColor{
    COLOR_BLACK   = 0,      ///< Black  text
    COLOR_RED     = 1,      ///< Red    text
    COLOR_GREEN   = 2,      ///< Green  text
    COLOR_YELLOW  = 3,      ///< Yellow text
    COLOR_BLUE    = 4,      ///< Blue   text
    COLOR_PURPLE  = 5,      ///< Purple text
    COLOR_CYAN    = 6,      ///< Cyan   text
    COLOR_WHITE   = 7,      ///< White  text
    COLOR_DEFAULT = 8       ///< Default color setting
};

/// @brief enum with text style variants
enum consoleStyle{
    STYLE_NORMAL     = 0,   ///< Normal         text style
    STYLE_BOLD       = 1,   ///< Bold           text style
    STYLE_UNDERLINED = 4,   ///< Underlined     text style
    STYLE_BLINKING   = 5,   ///< Blinking       text style
    STYLE_INVERT_C   = 7,   ///< Invert color   text style
    STYLE_INVISIBLE  = 8    ///< Invisible      text style
};

/**
 * @brief printf function with color and style settings
 * @param [in] color Text color
 * @param [in] style Text style
 * @param [in] text  Text value
*/
void color_printf(enum consoleColor color, enum consoleStyle style, const char* text, ...);

/**
 * @brief fprintf function with color and style settings
 * @param [out] stream Output flow
 * @param [in]  color  Text color
 * @param [in]  style  Text style
 * @param [in]  text   Text value
*/
void color_fprintf(FILE* stream, enum consoleColor color, enum consoleStyle style, const char* text, ...);

/**
 * @brief Function sets color and style for console
 * @param [in] stream Output stream 
 * @param [in] color  Text color
 * @param [in] style  Text style
 * @warning After printing all your data remember to set consoles default color and style
*/
void set_color(FILE* stream, enum consoleColor color, enum consoleStyle style);

/**
 * @brief putc function with color and style settings
 * @param [out] stream Output flow
 * @param [in]  color  Text color
 * @param [in]  style  Text style
 * @param [in]  ch     Char
*/
void color_putc(FILE* stream, enum consoleColor color, enum consoleStyle style, char ch);

/**
 * @brief fputs function with color and style settings
 * @param [out] stream Output flow
 * @param [in]  color  Text color
 * @param [in]  style  Text style
 * @param [in]  text   Text value
*/
void color_fputs(FILE* stream, enum consoleColor color, enum consoleStyle style, const char* text);

#endif