#ifndef TEXT_H
#define TEXT_H

#include <conio.h>
#include "../utils/screen.h"
#include "../utils/align.h"

#define TEXT_WIDTH 75

typedef struct Text {
    int x, y;
    char *label;
    Color *color;
    Align *align;
} Text;


void createText(int x, int y, const char *label, Color color, const Align align);

#endif