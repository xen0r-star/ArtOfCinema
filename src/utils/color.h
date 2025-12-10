#ifndef UTILS_COLOR_H
#define UTILS_COLOR_H


#include <stdio.h>

typedef struct ColorRGB {
    int r;
    int g;
    int b;
} ColorRGB;


void setColor(ColorRGB color);
void setBackground(ColorRGB background);
void resetColor();

#endif