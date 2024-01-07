// Created by Yide Fang
// Source file for the file handling.
//
#include "file.h"

/***
 * Will load eight hex encoded short values.  It is assumed there
 * will always be eight rooms, so this is a hard limit based on
 * the constant MAXROOMs
 * @param file_name
 */
void load_file(char *file_name) {

    // Stores file handler.
    FILE *input_file;

    // Open file and store result in file handler.
    input_file = fopen(file_name, "r");  // relative path name of file, read mode

    // Check the validity of the file handler.
    if (input_file == NULL) {
        // If error, print message to error stream and exit program.
        fprintf(stderr, "Error: unable to open file %s\n", file_name);
        exit(1);
    }

    // Loads the eight rooms as short hex encoded values.
    for (int i = 0; i < MAXROOMS; i++) {
        fscanf(input_file, "%4hx\n", &rooms[i]);
    }

    // Close the file handler.
    fclose(input_file);

    return;
}
