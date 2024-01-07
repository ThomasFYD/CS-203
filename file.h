// Created by Yide Fang
//
// The file module is very simple, just loading in 8 hexadecimal
// values into the external rooms unsigned short array.
//

#ifndef FISH_HAUS_FILE_H
#define FISH_HAUS_FILE_H

#include <stdio.h>
#include "bit_manip.h"

extern unsigned short rooms[MAXROOMS];

// Loads the file into the program, overwriting
// the shared rooms.
// file_name - Name of the file to load.
void load_file(char *file_name);

#endif //FISH_HAUS_FILE_H
