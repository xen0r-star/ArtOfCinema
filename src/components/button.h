#ifndef BUTTON_H
#define BUTTON_H

#include "../utils/screen.h"
#include "../utils/align.h"
#include "../utils/cursor.h"
#include "../utils/color.h"
#include "../theme/theme.h"


#define MAX_BUTTONS 10

typedef struct Button {
    int x, y;
    int width;
    ColorRGB color;
    const char* label;
    void (*onClick)(void);
} Button;


void createButton(int x, int y, int width, ColorRGB color, const char* label, void (*onClick)(void));

int deleteButton(Button *button);
void deleteAllButtons();

Button *getButton(int index);
int getButtonCount();

#endif