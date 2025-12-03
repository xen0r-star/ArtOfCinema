#ifndef TEXT_H
#define TEXT_H

#include <conio.h>
#include "../utils/screen.h"
#include "../utils/align.h"


typedef struct Text {
    int x, y;
    char *label;
    Color *color;
} Text;


void createText(int x, int y, const char *label, Color color);

#endif