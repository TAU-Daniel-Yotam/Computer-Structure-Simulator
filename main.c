
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Enum.h"
#include "Aux.h"

#define MEMSIZE 4096
#define NUMREGS 16

int main(int argc, const char * argv[]) {
    FILE*memin = fopen(argv[1], "r");
    FILE*memout = fopen(argv[2], "w");
    FILE*regout = fopen(argv[3], "w");
    FILE*trace = fopen(argv[4], "w");
    FILE*count = fopen(argv[5], "w");
    int memory[MEMSIZE]={0};
    int registers[NUMREGS] = {0};
    int inst_count=0;
    read_memory_file(memin,memory);
    int pc = 0;
    int instr[6]={0};
    int word = decode(memory[pc],instr);
    while(instr[0]!=HALT){
        write_trace(trace, word, pc, registers);
        pc++;
        switch(instr[0]){
            case ADD:
                add(instr,registers);
                break;
            case SUB:
                break;
            case AND:
                break;
            case OR:
                break;
            case SLL:
                break;
            case SRA:
                break;
            case MAC:
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
                break;
            case LW:
                break;
            case SW:
                break;
            case JR:
                break;
            case HALT:
                break;
        }
        inst_count++;
        word = decode(memory[pc],instr);
    }
    for(int i=0;i<MEMSIZE;i++){ // write memory contents to "memout"
        fprintf(memout, "%08X\n",memory[i]);
    }
    for(int i=0;i<NUMREGS;i++){ // write registers contents to "regout"
        fprintf(regout, "%08X\n",registers[i]);
    }
    fprintf(count, "%d",inst_count); // write instruction counter to "count"
    return 0;
}
