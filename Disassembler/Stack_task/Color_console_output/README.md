# Color_console_output
This is library of colored and stylish console output

#### Main function is `color_printf()`:
###### Code:

```c
void color_printf(enum consoleColor color, enum consoleStyle style, const char* text, ...)
{
    va_list arguments;
    va_start(arguments, text);

    printf("\33[%d;3%dm", style, color);
    vprintf(text, arguments);
    printf("\33[0;39m");
}
```

`color_printf()` works as default `printf()`, but has 2 additional parameters:
- color 
- style

###### color:
Parameter | Description
:---------|------------:
COLOR_BLACK   | Black  text
COLOR_RED     | Red    text
COLOR_GREEN   | Green  text
COLOR_YELLOW  | Yellow text
COLOR_BLUE    | Blue   text
COLOR_PURPLE  | Purple text
COLOR_CYAN    | Cyan   text
COLOR_WHITE   | White  text
COLOR_DEFAULT | Default color setting

###### style:
Parameter | Description
:---------|------------:
STYLE_NORMAL     | Normal         text style
STYLE_BOLD       | Bold           text style
STYLE_UNDERLINED | Underlined     text style
STYLE_BLINKING   | Blinking       text style
STYLE_INVERT_C   | Invert color   text style
STYLE_INVISIBLE  | Invisible      text style

#### Supporting function `set_color()`:
###### Code:

```c
void set_color(enum consoleColor color, enum consoleStyle style)
{
    printf("\33[%d;3%dm", style, color);
}
```

`set_color()` has 2 parameters:
- color 
- style

Parameters the same as the `color_printf()`

<b style="color:red">Warning:</b> remember to set default color after output colored data!