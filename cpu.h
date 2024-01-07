//
// Created by Thomas Fang on 11/4/23.
//

#ifndef CS_203_LAB_5_YIDE_FANG_CPU_H
#define CS_203_LAB_5_YIDE_FANG_CPU_H

#include "mem.h"

//define cpu registers and other variables
extern short R[4];          // General-purpose registers
extern short AC;            // Accumulator

extern unsigned short SP;            // Stack pointer
extern unsigned short BP;            // Base pointer

extern unsigned short PC;            // Program counter

extern struct MemoryLocation *IR;   // Instruction Register

//functions
//initialize the CPU
void initialize_cpu();

//fetch the next instruction
void fetch_instruction(struct MemoryLocation *memory);

//execute the current instruction
void execute_instruction();

//print the CPU's state
void print_cpu_state();


#endif //CS_203_LAB_5_YIDE_FANG_CPU_H