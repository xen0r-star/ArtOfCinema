#ifndef INPUT_H
#define INPUT_H

#include <conio.h>
#include "../utils/screen.h"
#include "../utils/cursor.h"
#include "../utils/align.h"
#include "../theme/theme.h"


#define INPUT_WIDTH 41
#define MAX_INPUTS 10

typedef struct Input {
    int x, y;
    char *label;
    char *placeholder;
    char *value;
    int isFocused;
} Input;


void createInput(int x, int y, const char *label, const char *placeholder);
void drawInputValue(Input *input);

int deleteInput(Input *input);
void deleteAllInputs();

Input *getInput(int index);
int getInputCount();


#endif