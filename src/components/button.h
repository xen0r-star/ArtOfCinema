#ifndef BUTTON_H
#define BUTTON_H

#include "../utils/screen.h"
#include "../utils/align.h"


#define MAX_BUTTONS 10


typedef enum Style {
    STYLE_DEFAULT,
    STYLE_BORDERLESS
} Style;

typedef struct Button {
    int x, y;
    int width;
    Color color;
    Style style;
    const char* label;
    void (*onClick)(void);
} Button;


void createButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void));

int deleteButton(Button *button);
void deleteAllButtons();

Button *getButton(int index);
int getButtonCount();

#endif