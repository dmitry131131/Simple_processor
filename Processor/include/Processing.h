/**
 * @file
 * @brief Main functions or processor
*/
#ifndef PROCESSING_H
#define PROCESSING_H

const int DOUBLE_COEF  = 10000;
const int COMMAND_PART = 0b11111;

#include "DSL.h"

struct softProcessorUnit {
    Stack stack;
    Stack retStack;
    int rax, rbx, rcx, rdx;
    size_t IP;
    char* CS;
    size_t commandCount;
};

/**
 * @brief Main processing function
 * @param [in] text Pointer to programm text
 * @return Error code or NO_ERRORS if everything is ok
*/
processorErrorCode processing(softProcessorUnit* processor);

processorErrorCode processor_push_from_register(softProcessorUnit* processor, registerNames reg);

processorErrorCode processor_pop(softProcessorUnit* processor, registerNames reg);

processorErrorCode processor_push(double num, Stack* stack);

processorErrorCode processor_out(Stack* stack, FILE* stream);

processorErrorCode processor_add(Stack* stack);

processorErrorCode processor_sub(Stack* stack);

processorErrorCode processor_mul(Stack* stack);

processorErrorCode processor_div(Stack* stack);

processorErrorCode processor_sqrt(Stack* stack);

processorErrorCode processor_trig(Stack* stack, commandCodes mode);

processorErrorCode processor_in(Stack* stack);

processorErrorCode processor_jmp(softProcessorUnit* processor, int ip);

processorErrorCode processor_ja(softProcessorUnit* processor, int ip);

processorErrorCode processor_jae(softProcessorUnit* processor, int ip);

processorErrorCode processor_jb(softProcessorUnit* processor, int ip);

processorErrorCode processor_jbe(softProcessorUnit* processor, int ip);

processorErrorCode processor_je(softProcessorUnit* processor, int ip);

processorErrorCode processor_jne(softProcessorUnit* processor, int ip);

enum processorErrorCode processor_hlt(Stack* stack);

#endif