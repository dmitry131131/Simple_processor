/**
 * @file
 * @brief Main functions or processor
*/
#ifndef PROCESSING_H
#define PROCESSING_H

#define USE_GRAPHICS

const int DOUBLE_COEF  = 10000;
const int COMMAND_PART = 0b11111;
const int ADDON_PART   = 0b11100000;
const unsigned int COMMAND_MASK = 0x000000FF;

const size_t RAM_SIZE       = 2701;
const size_t VRAM_SIZE      = 2601;
const size_t VRAM_ADRESS    = RAM_SIZE - VRAM_SIZE;
const unsigned int PIXEL_SIZE = 15;
const unsigned int WINDOW_SIZE = 52*PIXEL_SIZE;

const size_t STACK_SIZE     = 10;
const size_t RET_STACK_SIZE = 10;

#include "DSL.h"

struct softProcessorUnit {
    Stack stack;
    Stack retStack;
    int* RAM;
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

processorErrorCode processor_push_from_RAM(softProcessorUnit* processor, int adress);

processorErrorCode processor_pop_to_register(softProcessorUnit* processor, registerNames reg);

processorErrorCode processor_pop_to_RAM(softProcessorUnit* processor, int adress);

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

processorErrorCode processor_call(softProcessorUnit* processor, int ip);

processorErrorCode processor_ret(softProcessorUnit* processor);

processorErrorCode processor_console_draw(const softProcessorUnit* processor);

processorErrorCode processor_hlt(Stack* stack);

#endif