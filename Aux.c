
#include "Aux.h"
#define BUFSIZE 9 // 8 hex digits + '\0'

int read_line_by_line(FILE*f,char*line);

void read_memory_file(FILE*memin,int*memory){
    int i = 0;
    char line[BUFSIZ];
    while(!read_line_by_line(memin, line)){
        memory[i] = (int)strtol(line,NULL,16);
        i++;
    }
}

int decode(int word, int*inst){
    int temp = 0;
    int mask = 0x00000fff;
    temp = word & mask;
    inst[5] = temp;
    word >>= 12;
    mask = 0x0000000f;
    for(int i=4;i>=0;i--){
        temp = word & mask;
        inst[i] = temp;
        word >>= 4;
    }
    return word;
}

int read_line_by_line(FILE*f,char*line){
    char* readlen;
    int bufsize = BUFSIZE;
    if ((readlen = fgets(line, bufsize, f)) != NULL) {
        return 0;
    }
    return 1;
    
}

void write_trace(FILE*trace, int inst, int pc, int*regs){
    fprintf(trace,
            "%08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\r\n",
            pc,inst,regs[0],regs[1],regs[2],regs[3],regs[4],regs[5],regs[6],regs[7],regs[8],regs[9],regs[10],regs[11],regs[12],
            regs[13],regs[14],regs[15]);
}
