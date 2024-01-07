//
// Created by Thomas Fang on 11/4/23.
//

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Define memory array
struct MemoryLocation memory[ADDRESS_SIZE];

int loading_complete;    //mark program loading complete 标记程序（a sequence of instructions）加载完毕
int finalAddressUsed;    //record final address of program used 记录程序使用的最终内存地址

//Function to initialize memory
void initialize_memory() {
    // initialize memory to all zeros
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        memory[i].data = 0;
        memory[i].operation = data;
        memory[i].reg_a = -1;
        memory[i].reg_b = -1;
        memory[i].reg_c = -1;

        memory[i].immediate = -1;
        memory[i].address = -1;
        memory[i].index = -1;

        memory[i].instruction_str = NULL;
        memory[i].operator_str = NULL;
        memory[i].immediate_value_str = NULL;
        memory[i].address_value_str = NULL;
        memory[i].operand_a_str = NULL;
        memory[i].operand_b_str = NULL;
        memory[i].index_str = NULL;
    }
}

//define label struct标签
struct Label {
    char name[256];
    int address;
};

struct Label label_table[256];
int label_count = 0;

//Function to add a label to the label table
void add_label(const char *name, int address) {
    if(label_count < 256) {
        if(strlen(name) > sizeof(label_table[0].name)) {
            printf("Label name too long for the array: %s\n", name);
        } else{
            //put the new level
            strcpy(label_table[label_count].name, name);
            label_table[label_count].address = address;

            //increment the label count
            label_count++;
        }
    }
}

/*
 * resolve label 解析标签->返回标签地址
 *
 */
int resolve_label(const char *label_name) {
    for(int i = 0; i < label_count; i++) {
        if(strcmp(label_name, label_table[i].name) == 0) {
            return label_table[i].address;
        }
    }
}

/*
 * Function to load assembly code from a file into memory
 *
 * input: filename - the name of the file to load the assembly code from
 * output: none
 */
void load_program(const char *filename) {
    printf("start loading \n");
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    char line[256];
    int address = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove leading and trailing whitespace from the line
        char *start = line;
        char *end = line + strlen(line) - 1;
        while (start <= end && isspace((unsigned char)*start)) {
            start++;
        }
        while (end >= start && isspace((unsigned char)*end)) {
            end--;
        }
        end[1] = '\0';  // Null-terminate the trimmed string

        // Check if the line is empty or a comment
        if (start[0] == ';' || start[0] == '\0') {
            continue;  // Skip comments and empty lines
        }

        // Parse and store the instruction
        struct MemoryLocation *mem_loc = &memory[address];

        mem_loc->instruction_str = strdup(start);  // Store the original instruction string

        char *token = strtok(start, " \t,");
        if (token != NULL) {
            if (strcmp(token, "Lodi") == 0) {

                mem_loc->operation = lodi;
                mem_loc->reg_a=register_index(strtok(NULL, ","));
                mem_loc->immediate = atoi(strtok(NULL, " \t,"));


            } else if (strcmp(token, "Loda") == 0) {

                mem_loc->operation = loda;
                mem_loc->reg_a = register_index(strtok(NULL, ","));
                mem_loc->address = atoi(strtok(NULL, " \t,"));
            } else if (strcmp(token, "Sub") == 0) {

                mem_loc->operation = sub;
                mem_loc->reg_c = register_index(strtok(NULL, ","));
                mem_loc->reg_a = register_index(strtok(NULL, ","));
                mem_loc->reg_b = register_index(strtok(NULL, ","));

            }  else if (strcmp(token, "Add") == 0) {

                mem_loc->operation = add;
                mem_loc->reg_c = register_index(strtok(NULL, ","));
                mem_loc->reg_a = register_index(strtok(NULL, ","));
                mem_loc->reg_b = register_index(strtok(NULL, ","));

            }else if (strcmp(token, "Jmpn") == 0) {

                mem_loc->operation = jmpn;
                mem_loc->address_value_str = strdup(strtok(NULL, " \t,"));
                mem_loc->address=address;

            } else if (strcmp(token, "Jmpz") == 0) {

                mem_loc->operation = jmpz;
                mem_loc->address_value_str = strdup(strtok(NULL, " \t,"));
                mem_loc->address=address;

            }else if (strcmp(token, "Jmp") == 0) {

                mem_loc->operation = jmp;
                mem_loc->address_value_str = strdup(strtok(NULL, " \t,"));

            } else if (strcmp(token, "Call") == 0) {
                mem_loc->operation = call;
                mem_loc->address_value_str = strdup(strtok(NULL, " \t,"));

            }else if (strcmp(token, "Ret") == 0) {
                mem_loc->operation = ret;

            }
            else if (strcmp(token, "Addi") == 0) {

                mem_loc->operation = addi;
                mem_loc->reg_a = register_index(strtok(NULL, ","));
                mem_loc->immediate = atoi(strtok(NULL, " \t,"));
            } else if (strcmp(token, "Subi") == 0) {

                mem_loc->operation = subi;
                mem_loc->reg_a = register_index(strtok(NULL, ","));
                mem_loc->immediate = atoi(strtok(NULL, " \t,"));
            } else if (strcmp(token, "Halt") == 0) {

                mem_loc->operation = halt;

            } else if (strchr(token, ':') != NULL) {
                // Handle labels
                // You can implement label handling logic here

                char *labelName = strtok(token, ":"); // Tokenize the string at ':'
                add_label(labelName, address);

            }
        }

        address++;
    }

    loading_complete=1;
    finalAddressUsed=address-1;

    fclose(file);
}

/*
 * Function to dump the contents of memory
 *
 * input: filename - the name of the file to dump the memory contents to
 * output: none
 */
int register_index(char *reg){
    if(reg != NULL){
        //Skip leading whitespace
        reg += strspn(reg, " \t");

        if(strncmp(reg, "R", 1) == 0) {
            return atoi(reg + 1) - 1;
        } else {
            printf("Invalid register: %s\n", reg);
            return -1;
        }
    } else {
        printf("Register is null!\n");
        // Handle the error appropriately.
        return -1;
    }
}
