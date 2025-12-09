#ifndef TEXT_H
#define TEXT_H

#include <conio.h>
#include "../utils/screen.h"
#include "../utils/align.h"
#include "../utils/cursor.h"
#include "../utils/color.h"


typedef struct Text {
    int x, y;
    char *label;
    ColorRGB  *color;
} Text;


void createText(int x, int y, const char *label, ColorRGB  color);

#endif