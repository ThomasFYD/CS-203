// Created by Yide Fang
// The bit_manip module provides low-level functionality
// for manipulating the stored rooms value.  There is
// also verification and map presentation functionality
// to aid in game usage and system testing.
//

#ifndef FISH_HAUS_BIT_MANIP_H
#define FISH_HAUS_BIT_MANIP_H

#include <stdio.h>
#include <stdlib.h>

#define MAXROOMS 8

// Allows access to the global rooms array provided in the different
// source files containing the main.
extern unsigned short rooms[MAXROOMS];

// Initializes the game to start with room zero.
void initialize_rooms();

// Prints out the game map to ensure the game is correctly encoded.
void display_map();

// Retrieve the room number where the player is located.
short current_room();

// Checks the availability of one fish in the current room.
int one_fish_available();
int two_fish_available();
int red_fish_available();
int blue_fish_available();

// Modifies the current room so the one fish is not stored.
void pickup_one_fish();
void pickup_two_fish();
void pickup_red_fish();
void pickup_blue_fish();

// Modifies the current room so the one fish is now stored.
void putdown_one_fish();
void putdown_two_fish();
void putdown_red_fish();
void putdown_blue_fish();

// Returns the number of fish in the current room.
int cnt_fish_in_room();

// Checks if room n is adjacent to current room.
int room_n_accessible(int room);

// Checks if specified room is adjacent to current room.
int room_0_accessible();
int room_1_accessible();
int room_2_accessible();
int room_3_accessible();
int room_4_accessible();
int room_5_accessible();
int room_6_accessible();
int room_7_accessible();

// Determines if the pool is found in current room.
int pool_accessible();

// Stores current room back into memory and
// retrieves identified new room.
int change_room(short new_room);

// Sanity checks that the provided eight rooms follow
// the rules.
int verify_map();

#endif //FISH_HAUS_BIT_MANIP_H
