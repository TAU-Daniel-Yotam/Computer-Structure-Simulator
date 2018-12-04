
#include "Execute.h"


void add(int * instr,int * registers) {
    registers[instr[1]] = registers[instr[2]] + registers[instr[3]] + instr[5];
}
void sub(int * instr,int * registers){
    registers[instr[1]]=registers[instr[2]]-registers[instr[3]]-instr[5];
}
void And(int * instr,int *registers){
    registers[instr[1]]=registers[instr[2]]&registers[instr[3]]&instr[5];
}
void Or(int * instr,int *registers){
    registers[instr[1]]=registers[instr[2]]|registers[instr[3]]|instr[5];
}
void sll(int * instr,int *registers){
    registers[instr[1]]=registers[instr[2]]<<(registers[instr[3]]+instr[5]);
}
void sra(int * instr,int * registers){
    registers[instr[1]]=registers[instr[2]]>>(registers[instr[3]]+instr[5]);
}
void mac(int * instr,int *registers){
    registers[instr[1]]=registers[instr[2]]*registers[instr[3]]+registers[instr[4]]+instr[5];
}
void branch(int * instr,int * registers,int *pc){
    if (!registers[instr[4]]&&registers[instr[2]]==registers[instr[3]])
        *pc=instr[5];
    else if ((registers[instr[4]]==1)&&registers[instr[2]]!=registers[instr[3]])
        *pc=instr[5];
    else if ((registers[instr[4]]==2)&&registers[instr[2]]> registers[instr[3]])
        *pc=instr[5];
    else if ((registers[instr[4]]==3)&&registers[instr[2]]< registers[instr[3]])
        *pc=instr[5];
    else if ((registers[instr[4]]==4)&&registers[instr[2]]>= registers[instr[3]])
        *pc=instr[5];
    else if ((registers[instr[4]]==5)&&registers[instr[2]]<= registers[instr[3]])
        *pc=instr[5];
}
void jal(int * instr,int * registers,int * pc){
    register[15]=(*pc+1)&ONE;
    *pc=instr[5];
}
void lw(int * instr,int * mem,int * registers){
    registers[instr[1]]=mem[(registers[instr[2]]+instr[5])&ONE];
}
void sw(int * instr,int * mem,int * registers){
    mem[(registers[instr[2]]+instr[5])&ONE]=registers[instr[1]];
}

void jr(int * instr ,int * registers,int * pc){
    *pc=(registers[instr[1]]&ONE);
}







