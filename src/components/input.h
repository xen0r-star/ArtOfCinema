#ifndef INPUT_H
#define INPUT_H

#include "../utils/screen.h"


#define INPUT_WIDTH 41

typedef struct Input {
    int x, y;
    char *label;
    char *placeholder;
    char *value;
} Input;


void createInput(int x, int y, const char *label, const char *placeholder, const char *value);

#endif