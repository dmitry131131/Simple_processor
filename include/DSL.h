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
    JMP         = 14
};

enum registerNames {
    NO_REG  = 0,
    RAX     = 1,
    RBX     = 2,
    RCX     = 3,
    RDX     = 4
};

#endif