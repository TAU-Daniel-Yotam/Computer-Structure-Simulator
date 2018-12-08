
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Enum.h"
#include "Aux.h"
#include "Execute.h"

// to watch debug printing define DEBUG in "Execute.h"

#define MEMSIZE 4096
#define NUMREGS 16

int main(int argc, const char * argv[]) {
    FILE*memin = fopen(argv[1], "r");
    FILE*memout = fopen(argv[2], "w");
    FILE*regout = fopen(argv[3], "w");
    FILE*trace = fopen(argv[4], "w");
    FILE*count = fopen(argv[5], "w");
    int memory[MEMSIZE]={0}; //init memory
    int registers[NUMREGS] = {0}; //init registers
    int inst_count=0;
    read_memory_file(memin,memory); //load memin to memory
    int pc = 0;
    int instr[6]={0};
    int word = decode(memory[pc],instr); //decode next instruction
    while(instr[0]!=HALT){
#ifdef DEBUG
        printf("%08X\n",memory[pc]);
#endif
        write_trace(trace, word, pc, registers);
        pc++;
        switch(instr[0]){ //execute instruction
            case ADD:
                add(instr,registers);
                break;
            case SUB:
                sub(instr,registers);
                break;
            case AND:
                And(instr,registers);
                break;
            case OR:
                Or(instr,registers);
            case SLL:
                sll(instr,registers);
                break;
            case SRA:
                sra(instr,registers);
                break;
            case MAC:
                mac(instr,registers);
                break;
            case BRANCH:
                branch(instr,registers,&pc);
                break;
            case RES1:
                break;
            case RES2:
                break;
            case RES3:
                break;
            case JAL:
                jal(instr,registers,&pc);
                break;
            case LW:
                lw(instr,memory,registers);
                break;
            case SW:
                sw(instr,memory,registers);
                break;
            case JR:
                jr(instr,registers,&pc);
                break;
        }
        inst_count++;
        word = decode(memory[pc],instr);
    }
    inst_count++; //increment after halt instruction
    for(int i=0;i<MEMSIZE;i++){ // write memory contents to "memout"
        fprintf(memout, "%08X\n",memory[i]);
    }
    for(int i=0;i<NUMREGS;i++){ // write registers contents to "regout"
        fprintf(regout, "%08X\n",registers[i]);
    }
    fprintf(count, "%d",inst_count); // write instruction counter to "count"
    fclose(memin);
    fclose(memout);
    fclose(regout);
    fclose(trace);
    fclose(count);
    return 0;
}


