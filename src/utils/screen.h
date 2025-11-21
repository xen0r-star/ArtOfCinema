#ifndef UTILS_SCREEN_H
#define UTILS_SCREEN_H


#include <stdio.h>
#include <windows.h>


typedef enum Color {
    COLOR_BLACK = 30,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34,
    COLOR_MAGENTA = 35,
    COLOR_CYAN = 36,
    COLOR_WHITE = 37,
    COLOR_BRIGHT_BLACK = 90,
    COLOR_BRIGHT_RED = 91,
    COLOR_BRIGHT_GREEN = 92,
    COLOR_BRIGHT_YELLOW = 93,
    COLOR_BRIGHT_BLUE = 94,
    COLOR_BRIGHT_MAGENTA = 95,
    COLOR_BRIGHT_CYAN = 96,
    COLOR_BRIGHT_WHITE = 97
} Color;



int sizeScreen(int *columns, int *rows);
void clearScreen();

void cursor(int x, int y);
void hideCursor();
void showCursor();

void setColor(Color color);
void resetColor();


#endif