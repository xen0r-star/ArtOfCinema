#ifndef TEXT_H
#define TEXT_H

#include <conio.h>
#include "../utils/screen.h"
#include "../utils/align.h"

#define TEXT_WIDTH 75
#define MAX_TEXTS 10

typedef struct Text {
    int x, y;
    char *label;
    Color *color;
    Align *align;
    int isFocused;
} Text;


void createText(int x, int y, const char *label, Color color, const Align align);

int deleteText(Text *text);
void deleteAllTexts();

Text *getText(int index);
int getTextCount();

void redrawText(Text *text);

#endif