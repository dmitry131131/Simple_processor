#include <stdio.h>

#include "Stack.h"
#include "InputOutput.h"
#include "Read.h"
#include "Processing.h"

int main()
{
    textData* text = prepare("text.txt");

    processing(text);

    //output_text(text);
    return 0;
}