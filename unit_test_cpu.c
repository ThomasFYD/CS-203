//
// Created by Thomas Fang on 11/13/23.
//

#include <assert.h>
#include "cpu.h"
#include "mem.h"

// Test initialization of CPU
void test_initialize_cpu() {
    initialize_cpu();
    for (int i = 0; i < 4; i++) {
        assert(R[i] == 0);
    }
    assert(AC == 0);
    assert(SP == 0x100); // Assuming 0x100 is the expected initial value
    assert(BP == 0x100); // Assuming 0x100 is the expected initial value
    assert(PC == 0);     // Assuming 0 is the starting point of PC
    assert(IR == NULL);
}

// Test fetching an instruction
void test_fetch_instruction_cpu() {
    // Assuming memory is properly initialized
    // Initialize CPU
    initialize_cpu();

    // Set PC to a specific location
    PC = 5; // Assuming an instruction is at this location in memory

    fetch_instruction(memory);
    assert(IR == &memory[5]);
    assert(PC == 6); // PC should increment after fetch
}

// Test executing an instruction (example: add)
void test_execute_add_instruction_cpu() {
    // Set up the environment for an add instruction
    initialize_cpu();
    R[0] = 5;
    R[1] = 10;
    memory[0].operation = add;
    memory[0].reg_a = 0;
    memory[0].reg_b = 1;
    memory[0].reg_c = 2;

    IR = &memory[0];
    execute_instruction();

    assert(R[2] == 15);
    assert(AC == 15); // Assuming AC should hold the result
}

// Main function to run all tests
int main() {
    test_initialize_cpu();
    test_fetch_instruction_cpu();
    test_execute_add_instruction_cpu();
    return 0;
}