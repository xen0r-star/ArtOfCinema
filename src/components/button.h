#ifndef BUTTON_H
#define BUTTON_H

#include "../utils/screen.h"
#include "../utils/align.h"


#define MAX_BUTTONS 10
#define MAX_DATABUTTONS 10


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

typedef struct DataButton {
    int x, y;
    int width;
    Color color;
    Style style;
    const char* label;
    void (*onClick)(void*);
    void* data;
} DataButton;


void createButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void));
void createDataButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void*), void* data);


// Button functions
int deleteButton(Button *button);
void deleteAllButtons();

Button *getButton(int index);
int getButtonCount();


// DataButton functions
int deleteButtonData(DataButton *button);
void deleteAllDataButtons();

DataButton *getDataButton(int index);
int getDataButtonCount();

#endif