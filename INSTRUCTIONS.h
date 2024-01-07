//
// Created by Thomas Fang on 11/11/23.
//

#ifndef CS_203_LAB_5_YIDE_FANG_INSTRUCTIONS_H
#define CS_203_LAB_5_YIDE_FANG_INSTRUCTIONS_H

enum AssemblyInstruction {
    ADD,  // Addition
    SUB,  // Subtraction
    NEG,  // Negation
    MOVA, // Move to register from an address
    MOVR, // Move between registers
    LODI, // Load an immediate value to a register
    LODA, // Load from an address to a register
    LORR, // Load from memory using a register
    STOA, // Store to an address from a register
    STOR, // Store to memory using a register
    STOI, // Store immediate value to memory
    HALT, // Halt the program
    JMP,  // Jump to an address
    JMPZ, // Jump to an address if AC is zero
    JMPN, // Jump to an address if AC is negative
    CALL, // Call a function
    RET   // Return from a function
};

#endif //CS_203_LAB_5_YIDE_FANG_INSTRUCTIONS_H
