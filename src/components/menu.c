#include "menu.h"


static Menu menus[MAX_MENUS];
static int menu_count = 0;


void createMenu(int x, int y, int width, ColorRGB color, Style style, const char* title, Button *button1, Button *button2, Button *button3) {
    if (menu_count >= MAX_MENUS) return;

    int columns, rows;
    sizeScreen(&columns, &rows);

    if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, width);
    if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 3);

    menus[menu_count++] = (Menu){x, y, width, color, style, title, button1, button2, button3};

    if (style == STYLE_DEFAULT) {
        setColor(SECONDARY_COLOR);
        cursor(x, y);
        printf("\311");     // X
        for (int j = 0; j < width - 2; j++) printf("\315");
        printf("\273");     // ╗
        cursor(x, y+1);
        printf("\272");     // ║
        setColor(SECONDARY_COLOR);
        createText(x + (width - (int)strlen(_T(title))) / 2, y + 1, _T(title), color);
        setColor(SECONDARY_COLOR);

        cursor(x + width - 1, y + 1);
        printf("\272");
        // Création des 3 onglets (boutons)
        if (button1 != NULL) {
            createButton(button1->x, button1->y, button1->width, button1->label, button1->color, button1->style,  button1->onClick);
        }
        if (button2 != NULL) {
            createButton(button2->x, button2->y, button2->width, button2->label, button2->color, button2->style, button2->onClick);
        }
        if (button3 != NULL) {
            createButton(button3->x, button3->y, button3->width, button3->label, button3->color, button3->style, button3->onClick);
        }

        resetColor();

        if(button1 && button2 && button3){  
            // Ligne Y + 2 (Séparateur Titre / Boutons)
            cursor(x, y + 2); printf("\314"); // ╠
            for(int k=0; k<button1->width - 1; k++) printf("\315");
            printf("\313"); // ╦
            for(int k=0; k<button2->width - 1; k++) printf("\315");
            printf("\313"); // ╦
            for(int k=0; k<button3->width - 1; k++) printf("\315");
            printf("\271"); // ╣

            // Ligne Y + 3 (Verticales Boutons)
            cursor(x, y + 3); printf("\272");
            cursor(x + button1->width, y + 3); printf("\272");
            cursor(x + button1->width + button2->width, y + 3); printf("\272");
            cursor(x + width - 1, y + 3); printf("\272");

            // Ligne Y + 4 (Séparateur Boutons / Corps)
            cursor(x, y + 4); printf("\314"); // ╠
            for(int k=0; k<button1->width - 1; k++) printf("\315");
            printf("\312"); // ╩
            for(int k=0; k<button2->width - 1; k++) printf("\315");
            printf("\312"); // ╩
            for(int k=0; k<button3->width - 1; k++) printf("\315");
            printf("\271"); // ╣

            // Corps du menu
            for (int i = 5; i < rows - y - 4; i++){
                cursor(x, y + i); 
                printf("\272"); 
                cursor(x + width - 1, y + i); 
                printf("\272"); 
            }
            
        }else{
            for (int i = 2; i < rows - y - 4; i++){
                cursor(x, y + i); 
                printf("\272"); 
                cursor(x + width - 1, y + i); 
                printf("\272"); 
            }
            cursor(x, y+2);
            printf("\314");
            cursor(x + width - 1 , y + 2);
            printf("\271");

            cursor(x + 1, y + 2);
            for (int j = 0; j < width - 2; j++) printf("\315");
        }
        cursor(x, rows - 4);
        printf("\310");     // ╚
        for (int j = 0; j < width - 2; j++) printf("\315");
        printf("\274");     // ╝
    }
}


int deleteMenu(Menu *menu) {
    for (int i = 0; i < menu_count; i++) {
        if (&menus[i] == menu) {
            for (int j = i; j < menu_count - 1; j++) {
                menus[j] = menus[j + 1];
            }
            menu_count--;
            return 1;
        }
    }

    return 0;
}

void deleteAllMenus() {
    menu_count = 0;
}

Menu *getMenu(int index) {
    return &menus[index];
}

int getMenuCount() {
    return menu_count;
}