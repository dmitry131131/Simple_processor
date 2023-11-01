/**
 * @file
 * @brief Disassembler main functions
*/
#ifndef DISASSEMBLING_H
#define DISASSEMBLING_H

struct disassemblerCase {
    size_t IP;
    char* CS;
    size_t CS_len;
    size_t commandCount;
};

#include "DSL.h"

disassemblerErrorCode disassembling(disassemblerCase* disasmCase);

#endif