//
//  Aux.h
//  
//
//  Created by Yotam Manne on 01/12/2018.
//

#ifndef Aux_h
#define Aux_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_memory_file(FILE*memin,int*memory);
int decode(int word, int*inst);
void write_trace(FILE*trace, int inst, int pc, int*regs);

#endif /* Aux_h */
