
#ifndef Enum_h
#define Enum_h

#include <stdio.h>
/**
 Two enums for easy usage of register names and assembly operations
 */

typedef enum reg{
    ZERO= 0,
    AT  = 1,
    V0  = 2,
    A0  = 3,
    A1  = 4,
    T0  = 5,
    T1  = 6,
    T2  = 7,
    T3  = 8,
    S0  = 9,
    S1  = 10,
    S2  = 11,
    GP  = 12,
    SP  = 13,
    FP  = 14,
    RA  = 15
} reg;

typedef enum instrucion{
    ADD     = 0,
    SUB     = 1,
    AND     = 2,
    OR      = 3,
    SLL     = 4,
    SRA     = 5,
    MAC     = 6,
    BRANCH  = 7,
    RES1    = 8,
    RES2    = 9,
    RES3    = 10,
    JAL     = 11,
    LW      = 12,
    SW      = 13,
    JR      = 14,
    HALT    = 15
}inst;

#endif /* Enum_h */
