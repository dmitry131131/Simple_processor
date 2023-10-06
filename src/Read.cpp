#include <stdio.h>

#include "OneginError.h"
#include "InputOutput.h"
#include "Read.h"

textData* prepare(const char* filename)//assert nullptr
{
    static textData text = {};
    errorCode err = NO_ERRORS;

    CHECK_ERR_MAIN(get_text(filename, &text));

    return &text;
}