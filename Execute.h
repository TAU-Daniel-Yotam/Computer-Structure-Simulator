
#ifndef Execute_h
#define Execute_h
#include <stdio.h>
#define ONE 0xfff;

#endif /* Execute_h */
void add(int * instr,int * registers);
void sub(int * instr,int * registers);
void And(int * instr,int *registers);
void Or(int * instr,int *registers);
void sll(int * instr,int *registers);
void sra(int * instr,int * registers);
void mac(int * instr,int *registers);
void branch(int * instr,int * registers,int *pc);
void jal(int * instr,int * registers,int * pc);
void lw(int * instr,int * mem,int * registers);
void sw(int * instr,int * mem,int * registers);
void jr(int * instr,int * registers, int * pc);