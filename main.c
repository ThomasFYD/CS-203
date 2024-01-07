#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "cpu.h"

int main(int argc, char *argv[]){
    //run unit tests if -t is passed

    if(argc != 2) {
        printf("Usage error: %s <assembly_file>\n", argv[0]);
        return 1;
    }

    const char *assemblFileName = argv[1];

    //initialize memory and CPU
    initialize_cpu();
    initialize_memory();

    //load the program from the assembly file
    load_program(assemblFileName);

    //implement the fetch-decode-execute cycle loop
    if(loading_complete){
        while(1){
            fetch_instruction(memory);
            execute_instruction();

            //halt check
            if(IR->operation == halt){
                break;
            }
        }
    }

    //clean up and exit
    //deallocate any dynamic memory if necessary
    return 0;
}