// Created by Yide Fang
// Source file for bit manipulation.

#include "bit_manip.h"

/*** Variables specific to the bit-manipulation module. ***/
/*** These are not identified in the header file, and   ***/
/*** are hidden from the rest of the program.           ***/

// Stores the current room where the player is located.
// All manipulations will be against this stored value
// and must be stored before the player moves to the next
// room by overwriting this value.
unsigned short __current = 0;

// Defines masks for use in bit-manipulation functions below
unsigned short room_0_adj_bit = 0x0001; // mask: 0000 0000 0000 0001
unsigned short room_1_adj_bit = 0x0002; // mask: 0000 0000 0000 0010
unsigned short room_2_adj_bit = 0x0004; // mask: 0000 0000 0000 0100
unsigned short room_3_adj_bit = 0x0008; // mask: 0000 0000 0000 1000
unsigned short room_4_adj_bit = 0x0010; // mask: 0000 0000 0001 0000
unsigned short room_5_adj_bit = 0x0020; // mask: 0000 0000 0010 0000
unsigned short room_6_adj_bit = 0x0040; // mask: 0000 0000 0100 0000
unsigned short room_7_adj_bit = 0x0080; // mask: 0000 0000 1000 0000

unsigned short room_bits      = 0x0700; // mask: 0000 0111 0000 0000
unsigned short pool_bit       = 0x0800; // mask: 0000 1000 0000 0000

unsigned short one_fish_bit   = 0x1000; // mask: 0001 0000 0000 0000
unsigned short two_fish_bit   = 0x2000; // mask: 0010 0000 0000 0000
unsigned short red_fish_bit   = 0x4000; // mask: 0100 0000 0000 0000
unsigned short blue_fish_bit  = 0x8000; // mask: 1000 0000 0000 0000

/***
 * Initializes the game to start with room zero.
 */
void initialize_rooms() {
    __current = rooms[0];
}

/***
 * Prints out the game map to ensure the game is correctly encoded.
 */
void display_map() {

    puts("-- Game Map ----------------------------------------");

    // Displays the adjacency list for each room, staring with
    // zero room.
    puts("Adjacency Lists:");
    for (int i = 0; i < MAXROOMS; ++i) {

        // Change the room and print the name.
        change_room(i);
        printf(" room %d:", i);

        // Print the current room's adjacency list.
        for (int j = 0; j < MAXROOMS; ++j) {
            if(room_n_accessible(j)) {
                printf(" %d", j);
            }
        }
        printf("\n");
    }

    // Displays the room with the pool by walking through
    // the array looking for it.  If there are multiple
    // pools, then multiple pools will be printed.
    for (int i = 0; i < MAXROOMS; ++i) {
        change_room(i);
        if(pool_accessible()) {
            printf("\nRoom %d is the pool room.\n", i);
        }
    }

    // Displays the location of each of the four fish.
    // If there are multiple copies of each fish, then
    // mulitple locations will be displayed for each fish.
    printf("\nFish Locations:");
    for (int i = 0; i < MAXROOMS; ++i) {

        // Change to the new room identified by i.
        change_room(i);

        // Check for all four fish.
        if(one_fish_available()) {
            printf("\n Room %d: One Fish", i);
        }
        if(two_fish_available()) {
            printf("\n Room %d: Two Fish", i);
        }
        if(red_fish_available()) {
            printf("\n Room %d: Red Fish", i);
        }
        if(blue_fish_available()) {
            printf("\n Room %d: Blue Fish", i);
        }
    }

    puts("");
}

/***
 * Retrieve the room number from the stored room where
 * the player is located.
 * @return Provides the room number.
 */
short current_room() {
    // Retrieve the room number and shift bits to the
    // low-bit positions.
    return (__current & room_bits)  >> 8;
}

/***
 * Checks the availability of one fish in the current room.
 * @return Zero if fish is not available, and one if it is.
 */
int one_fish_available() {
    // Retrieve the one fish bit and return true if not zero.
    if(__current & one_fish_bit) return 1;
    return 0;
}

/***
 * Checks the availability of two fish in the current room.
 * @return Zero if fish is not available, and one if it is.
 */
int two_fish_available() {
    // Retrieve the two fish bit and return true if not zero.
    if(__current & two_fish_bit) return 1;
    return 0;
}

/***
 * Checks the availability of red fish in the current room.
 * @return Zero if fish is not available, and one if it is.
 */
int red_fish_available() {
    // Retrieve the red fish bit and return true if not zero.
    if(__current & red_fish_bit) return 1;
    return 0;
}

/***
 * Checks the availability of blue fish in the current room.
 * @return Zero if fish is not available, and one if it is.
 */
int blue_fish_available() {
    // Retrieve the blue fish bit and return true if not zero.
    if(__current & blue_fish_bit) return 1;
    return 0;
}

/***
 * If the one fish bit is set in current room, will
 * unset the bit using the xor operator.  Note, calling
 * this when the one fish bit is unset will set this bit.
 */
void pickup_one_fish() {
    __current = __current ^ one_fish_bit;
}

/***
 * If the two fish bit is set in current room, will
 * unset the bit using the xor operator.  Note, calling
 * this when the two fish bit is unset will set this bit.
 */
void pickup_two_fish() {
    __current = __current ^ two_fish_bit;
}

/***
 * If the red fish bit is set in current room, will
 * unset the bit using the xor operator.  Note, calling
 * this when the red fish bit is unset will set this bit.
 */
void pickup_red_fish() {
    __current = __current ^ red_fish_bit;
}

/***
 * If the blue fish bit is set in current room, will
 * unset the bit using the xor operator.  Note, calling
 * this when the blue fish bit is unset will set this bit.
 */
void pickup_blue_fish() {
    __current = __current ^ blue_fish_bit;
}

/***
 * Will set the one fish bit in the current room using the
 * or operator.  Note, calling this when the one fish bit
 * is set will leave this bit set.
 */
void putdown_one_fish() {
    __current = __current | one_fish_bit;
}

/***
 * Will set the two fish bit in the current room using the
 * or operator.  Note, calling this when the two fish bit
 * is set will leave this bit set.
 */
void putdown_two_fish() {
    __current = __current | two_fish_bit;
}

/***
 * Will set the red fish bit in the current room using the
 * or operator.  Note, calling this when the red fish bit
 * is set will leave this bit set.
 */
void putdown_red_fish() {
    __current = __current | red_fish_bit;
}

/***
 * Will set the blue fish bit in the current room using the
 * or operator.  Note, calling this when the blue fish bit
 * is set will leave this bit set.
 */
void putdown_blue_fish() {
    __current = __current | blue_fish_bit;
}

/***
 * This will count the number of fish in the current room,
 * with a maximum of four fish allowable.
 * @return The number of fish in the room.
 */
int cnt_fish_in_room() {
    int cnt = 0;
    if(one_fish_available())  cnt++;
    if(two_fish_available())  cnt++;
    if(red_fish_available())  cnt++;
    if(blue_fish_available()) cnt++;
    return cnt;
}

/***
 * Checks if a room is adjacent to the current room,
 * using the individual room checks.
 * @param room Number of the room being chence for adjacency.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_n_accessible(int room) {

    int ret = 0;

    switch(room) {
        case 0: {
            if(room_0_accessible()) ret = 1;
            break;
        }
        case 1: {
            if(room_1_accessible()) ret = 1;
            break;
        }
        case 2: {
            if(room_2_accessible()) ret = 1;
            break;
        }
        case 3: {
            if(room_3_accessible()) ret = 1;
            break;
        }
        case 4: {
            if(room_4_accessible()) ret = 1;
            break;
        }
        case 5: {
            if(room_5_accessible()) ret = 1;
            break;
        }
        case 6: {
            if(room_6_accessible()) ret = 1;
            break;
        }
        case 7: {
            if (room_7_accessible()) ret = 1;
            break;
        }
        default: {
            // This should not happen, but if it does the program
            // will display error and exit.
            printf("%s: Unknown room number passed: %d",
                   __FUNCTION__ , room);
            exit(-1);
        }
    }

    return ret;
}

/***
 * Checks if room 0 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_0_accessible() {
    // Retrieves room 0 bit and if not zero returns 1.
    if(__current & room_0_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 1 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_1_accessible() {
    // Retrieves room 1 bit and if not zero returns 1.
    if(__current & room_1_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 2 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_2_accessible() {
    // Retrieves room 2 bit and if not zero returns 1.
    if(__current & room_2_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 3 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_3_accessible() {
    // Retrieves room 3 bit and if not zero returns 1.
    if(__current & room_3_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 4 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_4_accessible() {
    // Retrieves room 4 bit and if not zero returns 1.
    if(__current & room_4_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 5 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_5_accessible() {
    // Retrieves room 5 bit and if not zero returns 1.
    if(__current & room_5_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 6 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_6_accessible() {
    // Retrieves room 6 bit and if not zero returns 1.
    if(__current & room_6_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if room 7 is adjacent to the current room.
 * @return Returns 1 if room is adjacent true and 0 if not adjacent.
 */
int room_7_accessible() {
    // Retrieves room 7 bit and if not zero returns 1.
    if(__current & room_7_adj_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Checks if the pool is in the current room.
 * @return Returns 1 if pool is there true and 0 if not.
 */
int pool_accessible() {
    // Retrieves the pool bit and if not zero returns 1.
    if(__current & pool_bit) return 1;
    // Otherwise returns 0.
    return 0;
}

/***
 * Will store the current room in its previous location
 * and load the identified new room.
 * @param new_room Number of the new room.
 * @return Returns one if change is successful, otherwise zero.
 */
int change_room(short new_room) {

    if(0 <= new_room && new_room < MAXROOMS) { // verify new room is valid

        // store current room back to memory
        rooms[current_room()] = __current;

        // retrieve new room from to memory
        __current = rooms[new_room];

    } else {

        // If room is not value, print error and return zero.
        fprintf(stderr, "%s: room number is out of bounds, value passed %d.",
             __FUNCTION__, new_room);
        return 0;
    }

    // if this is reached, then operation successful.
    return 1;
}

/***
 * Performs sanity checking of the provided rooms to ensure the rooms array is correctly
 * configured.
 * @return Returns one if all checks are passed, otherwise zero.
 */
int verify_map() {

    int ret = 1;       // Initialize the return code to indicate configuration is valid.
    int cnt_pools = 0; // Track the number of pools, there should be one.

    // Count the number of rooms that access each specific room.
    int room_accessible[MAXROOMS] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Count the number of adjacents, not including self-adjacency.
    int room_adjacent_cnt[MAXROOMS] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Tracks the numbers of each fish type, there should be one of each.
    int one_fish_cnt = 0;
    int two_fish_cnt = 0;
    int red_fish_cnt = 0;
    int blue_fish_cnt = 0;

    // Iterate through each room.
    for (int cnt = 0; cnt < MAXROOMS; cnt++) {

        // Count if room has a pool.
        if(rooms[cnt] & pool_bit    )  cnt_pools++;

        // Count number of each fish type in the room cnt.
        if(rooms[cnt] & one_fish_bit)  one_fish_cnt++;
        if(rooms[cnt] & two_fish_bit)  two_fish_cnt++;
        if(rooms[cnt] & red_fish_bit)  red_fish_cnt++;
        if(rooms[cnt] & blue_fish_bit) blue_fish_cnt++;

        // Count each of the adjacent rooms for current room,
        // ignoring if the count is equal to the current room.
        if(rooms[cnt] & room_0_adj_bit) {
            room_accessible[0]++;
            if(cnt != 0) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_1_adj_bit) {
            room_accessible[1]++;
            if(cnt != 1) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_2_adj_bit) {
            room_accessible[2]++;
            if(cnt != 2) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_3_adj_bit) {
            room_accessible[3]++;
            if(cnt != 3) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_4_adj_bit) {
            room_accessible[4]++;
            if(cnt != 4) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_5_adj_bit) {
            room_accessible[5]++;
            if(cnt != 5) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_6_adj_bit) {
            room_accessible[6]++;
            if(cnt != 6) room_adjacent_cnt[cnt]++;
        }
        if(rooms[cnt] & room_7_adj_bit) {
            room_accessible[7]++;
            if(cnt != 7) room_adjacent_cnt[cnt]++;
        }

    }
    puts("");

    // Determine if the number of one fish is more than one.
    if(one_fish_cnt > 1) {
        printf("Found %d one fish\n", one_fish_cnt);
        ret = 0;
    }

    // Determine if the number of two fish is more than one.
    if(two_fish_cnt > 1) {
        printf("Found %d two fish\n", two_fish_cnt);
        ret = 0;
    }

    // Determine if the number of red fish is more than one.
    if(red_fish_cnt > 1) {
        printf("Found %d red fish\n", red_fish_cnt);
        ret = 0;
    }

    // Determine if the number of blue fish is more than one.
    if(blue_fish_cnt > 1) {
        printf("Found %d blue fish\n", blue_fish_cnt);
        ret = 0;
    }

    // Verify room accessibility.
    for (int roomnum = 0; roomnum < MAXROOMS; roomnum++) {

        // Check if any rooms can access the current room roomnum.
        if(room_accessible[roomnum] == 0) {
            printf("Room %d is not accessible from any room.\n", roomnum);
            ret = 0;
        }


        // Check if any rooms can access the current room cnt.
        if(room_adjacent_cnt[roomnum] == 0) {
            printf("Room %d has no adjacent rooms.\n", roomnum);
            ret = 0;
        }
    }

    // Verify self-adjacency.
    if((rooms[0] & room_0_adj_bit) == 0) printf("Room 0 not self adjacent.\n");
    if((rooms[1] & room_1_adj_bit) == 0) printf("Room 1 not self adjacent.\n");
    if((rooms[2] & room_2_adj_bit) == 0) printf("Room 2 not self adjacent.\n");
    if((rooms[3] & room_3_adj_bit) == 0) printf("Room 3 not self adjacent.\n");
    if((rooms[4] & room_4_adj_bit) == 0) printf("Room 4 not self adjacent.\n");
    if((rooms[5] & room_5_adj_bit) == 0) printf("Room 5 not self adjacent.\n");
    if((rooms[6] & room_6_adj_bit) == 0) printf("Room 6 not self adjacent.\n");
    if((rooms[7] & room_7_adj_bit) == 0) printf("Room 7 not self adjacent.\n");

    return ret;
}

