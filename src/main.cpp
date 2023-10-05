#include <stdio.h>

#include "Error.h"
#include "Stack.h"
#include "InputOutput.h"
#include "Read.h"
#include "Processing.h"

int main()
{
    textData* text = prepare("text.txt");

    if (processing(text)) return 0;

    //output_text(text);
    return 0;
}