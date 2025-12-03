#ifndef UTILS_ALIGN_H
#define UTILS_ALIGN_H


#include <stdio.h>
#include <windows.h>
#include <limits.h>

#define ALIGN_LIMIT (INT_MAX - 100)

typedef enum HorizontalAlign {
    ALIGN_LEFT    = INT_MAX - 1,
    ALIGN_CENTER  = INT_MAX - 2,
    ALIGN_RIGHT   = INT_MAX - 3
} HorizontalAlign;

typedef enum VerticalAlign {
    ALIGN_TOP     = INT_MAX - 1,
    ALIGN_MIDDLE  = INT_MAX - 2,
    ALIGN_BOTTOM  = INT_MAX - 3
} VerticalAlign;


int HorizontalAlignment(const HorizontalAlign align, const int columns, const int size);
int VerticalAlignment(const VerticalAlign align, const int rows, const int size);

#endif