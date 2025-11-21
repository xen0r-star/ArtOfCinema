#ifndef BUTTON_H
#define BUTTON_H

#include "../utils/color.h"


typedef struct Button {
    int x, y;
    Color color;
    char *label;
    void (*onClick)(void);
};


Button *createButton(int x, int y, Color color, const char *label, void (*onClick)(void));

#endif