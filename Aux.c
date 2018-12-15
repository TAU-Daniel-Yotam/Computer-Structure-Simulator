
#include "Aux.h"
#define BUFSIZE 9 // 8 hex digits + '\0'

int read_line_by_line(FILE*f,char*line);


/**
 Reads all lines from the memory file and store it's values in an array

 @param memin - the file to read (input memory)
 @param memory - the array to fill with parsed integer values
 */
void read_memory_file(FILE*memin,int*memory){
    int i = 0;
    char line[BUFSIZ];
    while(!read_line_by_line(memin, line)){
        int a = (int)strtol(line,NULL,16);
        memory[i] = a;
        i++;
    }
}


/**
 Breaks a given int into 6 integer instruction arguments according to the format in the pdf.
 The function uses AND masks and shifts to extract the wanted bits for each argument.

 @param word - an integer (a word in the memory)
 @param inst - an array of size 6 that holds the inst. arguments
 @return word
 */
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
    if(!(inst[0] == 4 || inst[0] == 5 || inst[0] == 7 || inst[0] == 11)){ //sign extension if needed
        inst[5] <<= 20;
        inst[5] >>= 20;
    }
    return word;
}


/**
 Reads one line from the given file into a given buffer
 
 @param f - a file descriptor
 @param line - a buffer to read one line to
 @return 0 if one line was read or 1 if nothing was read (due to error or EOF)
 */
int read_line_by_line(FILE*f,char*line){
    char* readlen;
    int bufsize = BUFSIZE;
    if ((readlen = fgets(line, bufsize, f)) != NULL) {
        fseek(f, 2, SEEK_CUR); // skip \r\n
        return 0;
    }
    return 1;
    
}


/**
 Write the trace line before each instruction is executed

 @param trace - file descriptor
 @param inst - the original integer instruction
 @param pc - program counter
 @param regs - an array that represents all registers values
 */
void write_trace(FILE*trace, int inst, int pc, int*regs){
    fprintf(trace,
            "%08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\r\n",
            pc,inst,regs[0],regs[1],regs[2],regs[3],regs[4],regs[5],regs[6],regs[7],regs[8],regs[9],regs[10],regs[11],regs[12],
            regs[13],regs[14],regs[15]);
}
