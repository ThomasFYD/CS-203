//
// Created by Thomas Fang on 11/4/23.
//

#include "cpu.h"
#include "mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// instruction register referencing current instruction
short R[4];
short AC;
unsigned short SP;
unsigned short BP;
unsigned short PC;
struct MemoryLocation *IR;
static int firstTime = 1;
const char *operation_strings[] = {
        "data", "dumpmemory", "dumpCPU", "halt",
        "jmp", "jmpz", "jmpn", "call", "ret",
        "movac", "movr", "lodi", "loda",
        "lorr", "stoa", "stor", "stoi","sub",
        "addi","subi","add","neg"
};

void initialize_cpu() {
    // initialize general purpose registers to zero
    for (int i = 0; i < 4; i++) {
        R[i] = 0;
    }
    // initialize special purpose accumulator to zero
    AC = 0;
    // initialize stack pointer to the start of the stack
    SP = 0x100;
    // initialize base pointer to the start of the stack
    BP = 0x100;
    // initialize the program counter to the start of code memory
    PC = 0;
    // initialize the instruction register to empty
    IR = NULL;
}

void fetch_instruction(struct MemoryLocation *memory) {
    // fetch the instruction pointed to by the program counter
    IR = &memory[PC];
    PC++;  // increment the program counter
}

void execute_instruction(){
    if (IR == NULL) {
        // Handle the case where the instruction is not loaded
        printf("Instruction not loaded\n");
        return;
    }

    // Decode and execute the instruction based on the operation code
    switch (IR->operation) {
        case add:
            printf("add\n");
            // Perform addition using bitwise operators
            R[IR->reg_c] = R[IR->reg_a] + R[IR->reg_b];
            AC= R[IR->reg_c];
            printf("R[IR->reg_b] = %u and R[IR->reg_a] = %u\n",R[IR->reg_b],R[IR->reg_a]);
            break;
        case sub:
            printf("sub\n");
            // Perform subtraction using bitwise operators
            R[IR->reg_c] = R[IR->reg_b] - R[IR->reg_a];
            AC= R[IR->reg_c];
            printf("R[IR->reg_b] = %u and R[IR->reg_a] = %u\n",R[IR->reg_b],R[IR->reg_a]);
            break;
        case neg:
            printf("meg\n");
            // Perform negation using bitwise operators
            R[IR->reg_a] = -R[IR->reg_a];
            break;
        case lodi:
            printf("lodi\n");
            // Load an immediate value to a register
            R[IR->reg_a] = IR->immediate;
            break;
        case addi:
            printf("addi\n");
            // Add an immediate value to a register
            R[IR->reg_a] += IR->immediate;
            AC=R[IR->reg_a];
//printf("rega = %u", R[IR->reg_a]);
            break;
        case subi:
            printf("subi\n");
            // Subtract an immediate value from a register
            R[IR->reg_a] -= IR->immediate;
            AC=R[IR->reg_a];
            printf("AC = %hd\n",AC);
            break;
        case call:
            printf("call\n");

            if (firstTime  ) {
                printf("stack\n");
                SP = PC;
                firstTime=0;
            }
            PC = resolve_label(IR->address_value_str);
            break;
        case ret:
            printf("ret\n");
            PC = SP; // Return to the caller
            break;
        case jmp:
            printf("jmp\n");

            PC = resolve_label(IR->address_value_str) + 1;

            break;
        case jmpn:
            // Jump to an address if AC is negative

            if (AC < 0) {
                printf("jmpn\n");
                PC = resolve_label(IR->address_value_str) + 1;
            }
            break;
        case jmpz:

            // Jump to the specified address if AC is zero
            if (AC <= 0) {
                printf("Jmpz\n");
                PC = resolve_label(IR->address_value_str)+1;

            }
            break;
            // Implement the logic for other instructions.
        case halt:
            printf("HALT \n");
            // Halt the program
        default:
            // Handle unknown instructions or errors
            printf("Unknown instruction\n");
            break;
    }

}


void print_cpu_state() {
    printf("CPU State:\n");
    printf("PC: 0x%04X\n", PC);
    printf("AC: 0x%04X\n", AC);

    for (int i = 0; i < 4; i++) {
        printf("R%d: 0x%04X\n", i, R[i]);
    }
}