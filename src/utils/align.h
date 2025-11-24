#ifndef UTILS_ALIGN_H
#define UTILS_ALIGN_H


#include <stdio.h>
#include <windows.h>

typedef enum Align {
    LEFT,
    CENTER,
    RIGHT,
    DEF
} Align;


int AlignmentOBJ(const Align align, const int columns, const char *test);

#endif