/**
 * @file
 * @brief All crossproject info is here
*/
#ifndef DSL_H
#define DSL_H

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
    JMP         = 14,
    JA          = 15,
    JAE         = 16,
    JB          = 17,
    JBE         = 18,
    JE          = 19,
    JNE         = 20,
    CALL        = 21,
    RET         = 22
};

enum argumentsAddons {
    IMM  = 1 << 5,
    REG  = 1 << 6,
    RAM  = 1 << 7
};

enum registerNames {
    NO_REG  = 0,
    RAX     = 1,
    RBX     = 2,
    RCX     = 3,
    RDX     = 4
};

#endif