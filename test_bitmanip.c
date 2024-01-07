// Created by Yide Fang
// Source file for bit manipulation unit-testing.

#include <assert.h>
#include "bit_manip.h"

// Provides the global rooms array for unit-testing the
// bit-manipulation functions.  These are not initialized
// in the global space and are instead set in the main.
unsigned short rooms[MAXROOMS];

int main() {

    // first set of test rooms
    rooms[0] = 0x0801;
    rooms[1] = 0x0102;
    rooms[2] = 0x0204;
    rooms[3] = 0x0308;
    rooms[4] = 0x0410;
    rooms[5] = 0x0520;
    rooms[6] = 0x0640;
    rooms[7] = 0x0780;

    initialize_rooms();

    // Check adjacent-bit for room 0 in room 0, and
    // verify the room number works.
    assert(room_0_accessible() == 1);
    assert(current_room() == 0);

    // Check adjacent-bit for room 1 in room 1, and
    // verify the room number works.
    assert(change_room(1) == 1);
    assert(room_1_accessible() == 1);
    assert(current_room() == 1);

    // Check adjacent-bit for room 2 in room 2, and
    // verify the room number works.
    assert(change_room(2) == 1);
    assert(room_2_accessible() == 1);
    assert(current_room() == 2);

    // Check adjacent-bit for room 3 in room 3, and
    // verify the room number works.
    assert(change_room(3) == 1);
    assert(room_3_accessible() == 1);
    assert(current_room() == 3);

    // Check adjacent-bit for room 4 in room 4, and
    // verify the room number works.
    assert(change_room(4) == 1);
    assert(room_4_accessible() == 1);
    assert(current_room() == 4);

    // Check adjacent-bit for room 5 in room 5, and
    // verify the room number works.
    assert(change_room(5) == 1);
    assert(room_5_accessible() == 1);
    assert(current_room() == 5);

    // Check adjacent-bit for room 6 in room 6, and
    // verify the room number works.
    assert(change_room(6) == 1);
    assert(room_6_accessible() == 1);
    assert(current_room() == 6);

    // Check adjacent-bit for room 7 in room 7, and
    // verify the room number works.
    assert(change_room(7) == 1);
    assert(room_7_accessible() == 1);
    assert(current_room() == 7);

    // Check error condition, will print error of "value passed 8"
    assert(change_room(8) == 0);

    // verify pool check functions.
    assert(change_room(0) == 1);
    assert(pool_accessible() == 1);

    // test room verification function works
    rooms[0] = 0xF8FE;
    rooms[1] = 0xF9FE;
    rooms[2] = 0xFAFE;
    rooms[3] = 0xFBFE;
    rooms[4] = 0xFCFE;
    rooms[5] = 0xFDFE;
    rooms[6] = 0xFE00;
    rooms[7] = 0xFFFE;

    // Run the check to verify rooms, see run display.
    // Eight of each fish type should be found and eight pools should be found.
    // Room 0 can not be accessed from any room.
    // Room 6 has no adjacents and no self-adjacent.
    assert(!verify_map());

    // Set up fish unit-testing.
    rooms[0] = 0x00FF;
    rooms[1] = 0xF0FF;
    assert(change_room(0));

    // Check that there are no fish in the room.
    assert(one_fish_available() == 0);
    assert(two_fish_available() == 0);
    assert(red_fish_available() == 0);
    assert(blue_fish_available() == 0);

    // Add fish to the room.
    putdown_one_fish();
    putdown_two_fish();
    putdown_red_fish();
    putdown_blue_fish();

    // Check that fish are now in the room.
    assert(one_fish_available() == 1);
    assert(two_fish_available() == 1);
    assert(red_fish_available() == 1);
    assert(blue_fish_available() == 1);

    // Remove fish from the room.
    pickup_one_fish();
    pickup_two_fish();
    pickup_red_fish();
    pickup_blue_fish();

    // Check that fish are no longer in the room.
    assert(one_fish_available() == 0);
    assert(two_fish_available() == 0);
    assert(red_fish_available() == 0);
    assert(blue_fish_available() == 0);

    return 0;
}