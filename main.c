// Created by Yide Fang
// Source file for the main program.

#include <stdio.h>

#include "bit_manip.h"
#include "file.h"
#include "game.h"

// Provides the default global rooms array for the game
// These are initialized here, but will be overwritten
// by the file handling when a file is passed by the
// command-line.
unsigned short rooms[8] = {
        0x0007, // room 0
        0x011A, // room 1
        0x1264, // room 2
        0x2368, // room 3
        0x4458, // room 4
        0x85E0, // room 5
        0x06E0, // room 6
        0x0f81  // room 7
};

void display_commandline_format() {
    printf("Valid command-lines are:\n");
    printf("   ./fish_game default\n");
    printf("   ./fish_game file input_file.txt\n");
}

int main(int argc, char *argv[]) {

    if(argc < 2 || 3 < argc ) {
        printf("An incorrect number of command-line arguments past.\n\n");
        display_commandline_format();
    }

    if(*argv[1] == 'd') {

        // setup game and display game
        initialize_rooms();
        initialize_game();
        display_map();

        // setup game and play game
        initialize_rooms();
        initialize_game();

        while(!game_finished())
            play_turn();

        puts("Game Complete.");

    }
    else if(*argv[1] == 'f') {

        // Load from the command-line provided file.
        load_file(argv[2]);

        // setup game and display game
        initialize_rooms();
        initialize_game();
        display_map();

        // setup game and play game
        initialize_rooms();
        initialize_game();

        while(!game_finished())
            play_turn();

        puts("Game Complete.");

    }
    else {

        // Display error because the command-line arguments are incorrect.
        puts("Unknown command-line arguments passed.");
        display_commandline_format();
    }

    return 0;
}
