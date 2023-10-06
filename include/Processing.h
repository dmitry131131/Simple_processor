/**
 * @file
 * @brief Main functions or processor
*/
#ifndef PROCESSING_H
#define PROCESSING_H

const int DOUBLE_COEF = 10000;

/// @brief Enum with command codes
enum commandCodes {
    PUSH = 1,    
    ADD  = 2,
    SUB  = 3,
    MUL  = 4,
    DIV  = 5,
    OUT  = 6,
    SQRT = 7,
    SIN  = 8,
    COS  = 9,
    TAN  = 10,
    IN   = 11,
    HLT  = 12
};

struct softProcessorUnit {
    Stack stack;
    int rax, rbx, rcx, rdx;
    size_t IP;
    int* CS;
    size_t commandCount;
};

/**
 * @brief Main processing function
 * @param [in] text Pointer to programm text
 * @return Error code or NO_ERRORS if everything is ok
*/
enum processorErrorCode processing(textData* text);

enum processorErrorCode processor_push(const char* line, Stack* stack);

enum processorErrorCode processor_out(Stack* stack, FILE* stream);

enum processorErrorCode processor_add(Stack* stack);

enum processorErrorCode processor_sub(Stack* stack);

enum processorErrorCode processor_mue(Stack* stack);

enum processorErrorCode processor_div(Stack* stack);

enum processorErrorCode processor_sqrt(Stack* stack);

enum processorErrorCode processor_trig(Stack* stack, int mode);

enum processorErrorCode processor_in(Stack* stack, FILE* inputStream);

enum processorErrorCode processor_hlt(Stack* stack);

#endif