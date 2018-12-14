
#include "Execute.h"

//R[rd] = R[rs] + R[rt] + simm
void add(int * instr,int * registers) {
    #ifdef DEBUG
    printf("add $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    printf("$%d<- %d + %d + %d\n",instr[1], registers[instr[2]], registers[instr[3]], instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] + registers[instr[3]] + instr[5];
}

//R[rd] = R[rs] – R[rt] – simm
void sub(int * instr,int * registers){
    #ifdef DEBUG
    printf("sub $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    printf("$%d<- %d - %d - %d\n",instr[1], registers[instr[2]], registers[instr[3]], instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] - registers[instr[3]] - instr[5];
}

//R[rd] = R[rs] & R[rt] & simm
void And(int * instr,int *registers){
    #ifdef DEBUG
    printf("and $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] & registers[instr[3]] & instr[5];
}

//R[rd] = R[rs] | R[rt] | simm
void Or(int * instr,int *registers){
    #ifdef DEBUG
    printf("or $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] | registers[instr[3]] | instr[5];
}

//R[rd] = R[rs] << [R[rt] + imm]
void sll(int * instr,int *registers){
    #ifdef DEBUG
    printf("sll $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] << (registers[instr[3]] + instr[5]);
}

//R[rd] = R[rs] >> [R[rt] + imm]
void sra(int * instr,int * registers){
    #ifdef DEBUG
    printf("sra $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] >> (registers[instr[3]] + instr[5]);
}

//R[rd] = R[rs] * R[rt] + R[rm] + simm
void mac(int * instr,int *registers){
    #ifdef DEBUG
    printf("mac $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    printf("$%d<- %d * %d + %d + %d\n",instr[1], registers[instr[2]], registers[instr[3]], registers[instr[4]], instr[5]);
    #endif
    registers[instr[1]] = registers[instr[2]] * registers[instr[3]] + registers[instr[4]] + instr[5];
}

//if ((rm == 0) && (R[rs] == R[rt])) pc = imm
//if ((rm == 1) && (R[rs] != R[rt])) pc = imm
//￼￼￼￼￼￼￼￼￼￼if ((rm == 2) && (R[rs] > R[rt])) pc = imm
//if ((rm == 3) && (R[rs] < R[rt])) pc = imm
//if ((rm == 4) && (R[rs] >= R[rt])) pc = imm
//if ((rm == 5) && (R[rs] <= R[rt])) pc = imm
void branch(int * instr,int * registers,int *pc){
    #ifdef DEBUG
    printf("branch $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    printf("rm: %d, r[rs]: %d, r[rt]: %d, imm: %d\n",instr[4],registers[instr[2]],registers[instr[3]],instr[5]);
    #endif
    if (!instr[4] && registers[instr[2]] == registers[instr[3]])
        *pc=instr[5];
    else if ((instr[4] == 1) && registers[instr[2]] != registers[instr[3]])
        *pc=instr[5];
    else if ((instr[4] == 2) && registers[instr[2]] > registers[instr[3]])
        *pc=instr[5];
    else if ((instr[4] == 3) && registers[instr[2]] < registers[instr[3]])
        *pc=instr[5];
    else if ((instr[4] == 4) && registers[instr[2]] >= registers[instr[3]])
        *pc=instr[5];
    else if ((instr[4] == 5) && registers[instr[2]] <= registers[instr[3]])
        *pc=instr[5];
}

//R[15] = (pc + 1) & 0xfff (next instruction address), pc = imm
void jal(int * instr,int * registers,int * pc){
    #ifdef DEBUG
    printf("jal $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[15] = (*pc) & ONE;
    *pc=instr[5];
}

//￼￼R[rd] = MEM[(R[rs]+simm) & 0xfff]
void lw(int * instr,int * mem,int * registers){
    #ifdef DEBUG
    printf("lw $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    registers[instr[1]] = mem[(registers[instr[2]] + instr[5]) & ONE];
}

//MEM[(R[rs]+simm) & 0xfff] = R[rd]
void sw(int * instr,int * mem,int * registers){
    #ifdef DEBUG
    printf("sw $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    mem[(registers[instr[2]] + instr[5]) & ONE] = registers[instr[1]];
}

//pc = R[rd] & 0xfff
void jr(int * instr ,int * registers,int * pc){
    #ifdef DEBUG
    printf("jr $%d $%d $%d $%d %d\n",instr[1],instr[2],instr[3],instr[4],instr[5]);
    #endif
    *pc=(registers[instr[1]] & ONE);
}







