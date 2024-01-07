// Created by Yide Fang
// Source file for higher-level game handling.

#include "game.h"

// Tracks which fish the player has.
int player_has_one_fish  = 0;
int player_has_two_fish  = 0;
int player_has_red_fish  = 0;
int player_has_blue_fish = 0;

/*** Module only functions ***/

/***
 * Return the total number of fish in the current room.
 * Function is not available beyond this module.
 * @return The count of fish.
 */
int cnt_player_fish () {
    int cnt = 0;
    if(player_has_one_fish)  cnt++;
    if(player_has_two_fish)  cnt++;
    if(player_has_red_fish)  cnt++;
    if(player_has_blue_fish) cnt++;
    return cnt;
}

/***
 * Displays the selections as described in the assignment.
 * Function is not available beyond this module.
 * @return
 */
int display_selection() {

    // Sets up a variable for storing the count of fish in a room.
    int fish_cnt       = 0;
    // Tracks the option number.
    int option_counter = 0;

    puts("---------------------------------------\n");

    // Displays the current room number.
    printf("Room Number : %d\n", current_room());

    // Print possible rooms.
    puts("\nRoom Movement Selection:\n");

    // Display the possible rooms that can be moved to.
    for (int cnt = 0; cnt < MAXROOMS; cnt++) {

        if(room_n_accessible(cnt)) {
            if(current_room() == cnt)
                printf(" %2d - stay in room %d\n", option_counter, cnt);
            else
                printf(" %2d - move to room %d\n", option_counter, cnt);
            option_counter++;
        }

    }

    // Display fish player has.
    printf("\nFish you have  : ");
    fish_cnt = cnt_player_fish();

    // Display one fish.
    if(player_has_one_fish) {
        printf("one fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display two fish.
    if(player_has_two_fish)   {
        printf("two fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display red fish.
    if(player_has_red_fish)   {
        printf("red fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display blue fish.
    if(player_has_blue_fish)  {
        printf("blue fish");
        fish_cnt--;
    }

    // Prints a period if there is at least one fish listed.
    if(cnt_player_fish() > 0) puts(".");

    // print available fish
    printf("\nAvailable fish : ");
    fish_cnt = cnt_fish_in_room();

    // Display one fish.
    if(one_fish_available()) {
        printf("one fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display two fish.
    if(two_fish_available())   {
        printf("two fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display red fish.
    if(red_fish_available())   {
        printf("red fish");
        if(fish_cnt > 1) {
            printf(", ");
            fish_cnt--;
        }
    }

    // Display blue fish.
    if(blue_fish_available())  {
        printf("blue fish");
    }

    // Prints a period if there is at least one fish listed.
    if(cnt_fish_in_room() > 0) puts(".");
    else puts("");

    printf("\nFish Options:\n\n");

    // print putdown actions
    if(player_has_one_fish) {
        printf(" %2d - put down one fish.\n", option_counter++);
    }
    if(player_has_two_fish)   {
        printf(" %2d - put down two fish.\n", option_counter++);
    }
    if(player_has_red_fish)   {
        printf(" %2d - put down red fish.\n", option_counter++);
    }
    if(player_has_blue_fish)  {
        printf(" %2d - put down blue fish.\n", option_counter++);
    }

    // print pickup actions
    if(one_fish_available()) {
        printf(" %2d - pickup one fish.\n", option_counter++);
    }
    if(two_fish_available()) {
        printf(" %2d - pickup two fish.\n", option_counter++);
    }
    if(red_fish_available()) {
        printf(" %2d - pickup red fish.\n", option_counter++);
    }
    if(blue_fish_available()) {
        printf(" %2d - pickup blue fish.\n", option_counter++);
    }

    // This should contain the largest options value.
    return option_counter;
}

/***
 * Processes the action, using the option value to detect what
 * action was requested.  This is done by decrementing the option
 * value with each possibility.  This function is paired with the
 * display selection, and must remained synchronized.
 * Function is not available beyond this module.
 * @param option - The option number selected.
 * @return The final optimized value after it has been decremented.
 *         If option is successfully selected, then this value will
 *         be zero.
 */
int perform_actions(int option) {

    // process room movements
    for (int cnt = 0; cnt < MAXROOMS; cnt++) {

        if(room_n_accessible(cnt)) {

            // Room is accessible now check if option is zero.
            // If so, then change the room to the new location,
            // if not, then reduce option value.
            if(option > 0) option--;
            else {
                change_room(cnt);
                return option;
            }
        }
    }

    // process the player fish actions
    if(player_has_one_fish) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            putdown_one_fish();
            player_has_one_fish = 0;
            return option;
        }
        else option--;
    }

    if(player_has_two_fish) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            putdown_two_fish();
            player_has_two_fish = 0;
            return option;
        }
        else option--;
    }

    if(player_has_red_fish) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            putdown_red_fish();
            player_has_red_fish = 0;
            return option;
        }
        else option--;
    }

    if(player_has_blue_fish) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            putdown_blue_fish();
            player_has_blue_fish = 0;
            return option;
        }
        else option--;
    }

    // process the room fish actions
    if(one_fish_available()) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            pickup_one_fish();
            player_has_one_fish = 1;
            return option;
        }
        else option--;
    }

    if(two_fish_available()) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            pickup_two_fish();
            player_has_two_fish = 1;
            return option;
        }
        else option--;
    }

    if(red_fish_available()) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            pickup_red_fish();
            player_has_red_fish = 1;
            return option;
        }
        else option--;
    }

    if(blue_fish_available()) {
        // If option is zero, perform action, otherwise
        // decrement option and continue.
        if(option == 0) {
            pickup_blue_fish();
            player_has_blue_fish = 1;
            return option;
        }
        else option--;
    }

    // If this state is reached then the passed option was incorrect.
    return option;
}

/*** Functions available beyond module. ***/

/***
 * Initialize the player game variables.
 */
void initialize_game() {

    player_has_one_fish = 0;
    player_has_two_fish = 0;
    player_has_red_fish = 0;
    player_has_blue_fish = 0;

}


/***
 * Processes a single turn.
 */
void play_turn() {

    short input_value; // Item retrieved from stdin.

    // Displays the current room number, available fish, and
    // the different options the player has to them.
    int option_cnt = display_selection();

    // Requests the player to enter one option.
    printf("\nSelect Option : ");
    scanf("%hd", &input_value);

    // Validates the provided value. If input is not valid then
    // the program will repeated request a new value.
    while (input_value < 0  || option_cnt <= input_value) {
        printf("\n%d is not valid option, select value in range 0 to %d.", input_value, option_cnt - 1);
        printf("\nSelect Option : ");
        scanf("%hd", &input_value);
    }

    // Once a valid input is provided, then the program acts upon the action.
    perform_actions(input_value);

    return;
}

/***
 * Verifies that all the fish are in the room containing the pool.
 * @return If all fish are in pool room then return 1, otherwise return 0.
 */
int game_finished() {

    int ret = 1; // Initialize to winning game.

    /*** If any of the following are true, then game not finished. ***/

    if(!pool_accessible())     ret = 0; // Check if not in room with pool.

    if(!one_fish_available())  ret = 0; // Check if one fish not in room.
    if(!two_fish_available())  ret = 0; // Check if two fish not in room.
    if(!red_fish_available())  ret = 0; // Check if red fish not in room.
    if(!blue_fish_available()) ret = 0; // Check if blue fish not in room.

    return ret; // Return final result.
}
