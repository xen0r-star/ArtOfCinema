#ifndef MENU_H
#define MENU_H

#include "../utils/screen.h"
#include "../utils/align.h"

#include "../components/logo.h"
#include "../components/footer.h"
#include "../components/text.h"
#include "../components/input.h"
#include "../components/button.h"
#include "../components/language.h"


#define MAX_MENUS 5


typedef enum Style {
    STYLE_DEFAULT,
    STYLE_BORDERLESS
} Style;

typedef struct Menu {
    int x, y;
    int width;
    Color color;
    Style style;
    const char* title;
    Button *button1;     // Peut-être NULL
    Button *button2;     // Peut-être NULL
    Button *button3;     // Peut-être NULL
} Menu;


void createMenu(int x, int y, int width, Color color, Style style, const char* title, Button *button1, Button *button2, Button *button3);

int deleteMenu(Menu *menu);
void deleteAllMenu();

Menu *getMenu(int index);
int getMenuCount();

#endif