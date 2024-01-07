//
// Created by Thomas Fang on 11/4/23.
//

#ifndef CS_203_LAB_5_YIDE_FANG_MEM_H
#define CS_203_LAB_5_YIDE_FANG_MEM_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//include the instructions header for enum OP
#include "INSTRUCTIONS.h"

// defines the size of a pointer
#define ADDRESS_SIZE 65536

enum OP {
    data, // indicates location stores data
    dumpmemory, // dump the contents of memory to stdout
    dumpCPU, // dump the contents of the CPU to stdout
    halt, // halts program
    jmp, jmpz, jmpn, // jump instructions
    call, ret, // function call/ret instructions
    movac, movr, // register move instructions
    lodi, loda, lorr, // memory load instructions reg --> memory
    stoa, stor, stoi, // memory store instructions memory --> reg
    add, addi, sub, subi, neg // arithmetic instructions
};

struct MemoryLocation {
    unsigned short data;// data stored at location
    enum OP operation; // enum indicating operator being performed
    short reg_a; // the index of register a
    short reg_b; // the index of register b
    short reg_c; // the index of register c
    short immediate; // immediate value
    short address; // address value
    short index; // index value
    char *instruction_str; // original string from file
    char *operator_str;// The substring identify operator being performed.
    char *immediate_value_str;// The substring identify immediate value.
    char *address_value_str;// The substring identify address value.
    char *operand_a_str;// The substring identify operand a.
    char *operand_b_str;// The substring identify operand b.
    char *index_str;// The substring identify index.
};

//Declare the memory array here as a global variable
extern struct MemoryLocation memory[ADDRESS_SIZE];
extern int loading_complete;    //标记程序（a sequence of instructions）加载完毕
extern int finalAddressUsed;    //记录程序使用的最终内存地址

//Function to initialize memory
void initialize_memory();

//Function to load assembly code from a file into memory
void load_program(const char *filename);
int register_index(char *reg_str);
extern int resolve_label(const char *label_name);
void add_label(const char *name, int address);

#endif //CS_203_LAB_5_YIDE_FANG_MEM_H
