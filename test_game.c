// Created by Yide Fang
// Source file for game system testing.

#include "game.h"

// Provides the global rooms array for game system testing
// functions.  These are initialized in the global space
// and then do not change in the main.
unsigned short rooms[MAXROOMS] = {
        0xF003,
        0X0902,
        0X0204,
        0X0308,
        0X0410,
        0X0520,
        0X0640,
        0X0780,
};

int main() {

    // Required to set up the game.
    initialize_rooms();
    initialize_game();

    // sets up a specific set of moves to allow picking up
    // all the fish from one room, then move to room with
    // the pool, and leave fish in new room.
    play_turn(); // pickup fish tests
    play_turn();
    play_turn();
    play_turn();

    play_turn(); // move to pool-room test

    play_turn(); // put down fish tests
    play_turn();
    play_turn();
    play_turn();

    // After the previous actions, checks if the game is finished.
    if(game_finished()) {
        printf("Game Over!");
    }

    return 0;
}