/**
 * @file
 * @brief Main functions or processor
*/
#ifndef PROCESSING_H
#define PROCESSING_H

const int DOUBLE_COEF = 10000;

/// @brief Enum with command codes
enum commandCodes {
    NO_COMMAND  = 0,
    PUSH        = 1,    
    ADD         = 2,
    SUB         = 3,
    MUL         = 4,
    DIV         = 5,
    OUT         = 6,
    SQRT        = 7,
    SIN         = 8,
    COS         = 9,
    TAN         = 10,
    IN          = 11,
    HLT         = 12,
    POP         = 13,
    JMP         = 14
};

enum registerNames {
    NO_REG  = 0,
    RAX     = 1,
    RBX     = 2,
    RCX     = 3,
    RDX     = 4
};

struct softProcessorUnit {
    Stack stack;
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
enum processorErrorCode processing(softProcessorUnit* processor);

processorErrorCode processor_push_from_register(softProcessorUnit* processor, registerNames reg);

processorErrorCode processor_pop(softProcessorUnit* processor, registerNames reg);

enum processorErrorCode processor_push(double num, Stack* stack);

enum processorErrorCode processor_out(Stack* stack, FILE* stream);

enum processorErrorCode processor_add(Stack* stack);

enum processorErrorCode processor_sub(Stack* stack);

enum processorErrorCode processor_mul(Stack* stack);

enum processorErrorCode processor_div(Stack* stack);

enum processorErrorCode processor_sqrt(Stack* stack);

enum processorErrorCode processor_trig(Stack* stack, commandCodes mode);

enum processorErrorCode processor_in(Stack* stack);

enum processorErrorCode processor_hlt(Stack* stack);

#endif