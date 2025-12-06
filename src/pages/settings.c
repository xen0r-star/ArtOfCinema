#include "settings.h"


static void test1(){
    cursor(10,10);
    printf("TEST1");
    Sleep(2000);
    cursor(10,10);
    printf("LAST1");
}

static void test2(){
    cursor(10,10);
    printf("TEST2");
    Sleep(2000);
    cursor(10,10);
    printf("LAST2");
}

static void test3(){
    cursor(10,10);
    printf("TEST3");
    Sleep(2000);
    cursor(10,10);
    printf("LAST3");
}

static void createMenu(int x, int y, ColorRGB color, int width){
    // Alignement ...
    setColor(SECONDARY_COLOR);
    cursor(x, y);
                
    printf("\311");     // X
    for (int j = 0; j < width - 2; j++) printf("\315");
    printf("\273");     // ╗
    cursor(x, y+1);
    printf("\272");     // ║
    setColor(color);
    createText(x + (width - (int)strlen(_T("setting.menu.label"))) / 2, y + 1, _T("setting.menu.label"), (ColorRGB){78, 78, 78});
    setColor(SECONDARY_COLOR);

    cursor(x + width - 1, y + 1);
    printf("\272");
    // Création des 3 onglets (boutons)
    createButton(x, y + 2, 12, SECONDARY_COLOR, _T("setting.menu.o1"), test1);
    createButton(x + 11, y + 2, 13, SECONDARY_COLOR, _T("setting.menu.o2"), test2);
    createButton(x + 23, y + 2, 15, SECONDARY_COLOR, _T("setting.menu.o3"), test3);
    // Modifications des caratères nécessaires
    cursor(x, y + 2);     // Y + 2
    printf("\314");     // ╠
    cursor(x + 11, y + 2);
    printf("\313");     // ╦
    cursor(x + 23, y + 2);
    printf("\313");
    cursor(x + width - 1, y + 2);
    printf("\271");     // ╣
    cursor(x, y + 4);     // Y + 4
    printf("\314");
    cursor(x + 11, y + 4);
    printf("\312");     // ╩
    cursor(x + 23, y + 4);
    printf("\312");
    cursor(x + width - 1, y + 4);
    printf("\271");     
    cursor(x, y + 5);
    printf("\310");     // ╚
    for (int j = 0; j < width - 2; j++) printf("\315");
    printf("\274");     // ╝
}

static void initMenu(int columns,int rows, int width){
    createMenu((columns-width)/2, rows/2, (ColorRGB){255, 255, 255}, width);
}

void showSettingsPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLanguage();
    buttonClose();

    createText(ALIGN_CENTER, 10, _T("settings.visual.txt"), (ColorRGB){0, 255, 0});
    // Calcul taille de la fenêtre paramètres (+ 12 espaces & +4 caractères)
    int width = (int)strlen(_T("setting.menu.o1")) +
                (int)strlen(_T("setting.menu.o2")) + 
                (int)strlen(_T("setting.menu.o3")) +
                16;
    initMenu(columns, rows, width);
}