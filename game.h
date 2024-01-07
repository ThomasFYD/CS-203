// Created by Yide Fang
//
// The game module provides higher level functionality,
// for running turns and checking if game over.
//

#ifndef FISH_HAUS_GAME_H
#define FISH_HAUS_GAME_H

#include "bit_manip.h"

// Allows access to the global rooms array provided in the different
// source files containing the main.
extern unsigned short rooms[MAXROOMS];

// Initialize the player game variables.
void initialize_game();

// Processes a single turn.
void play_turn();

// Verifies that all the fish are in the room containing the pool.
int game_finished();

#endif //FISH_HAUS_GAME_H
