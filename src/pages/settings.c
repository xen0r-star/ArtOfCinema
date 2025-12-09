#include "settings.h"


static void test1(){
    cursor(10,10);
    printf("TEST1");
    // Sleep(2000);
    cursor(10,10);
    printf("LAST1");
}

static void test2(){
    cursor(10,10);
    printf("TEST2");
    // Sleep(2000);
    cursor(10,10);
    printf("LAST2");
}

static void test3(){
    cursor(10,10);
    printf("TEST3");
    // Sleep(2000);
    cursor(10,10);
    printf("LAST3");
}

static void initMenu(int columns,int rows, int width){
    int x = (columns-width)/2;
    int y = (rows/2)-3;

    Button btn1 = {x, y + 2, 12, SECONDARY_COLOR, STYLE_BORDERLESS, _T("setting.menu.o1"), test1};
    Button btn2 = {x + 12, y + 2, 12, SECONDARY_COLOR, STYLE_BORDERLESS, _T("setting.menu.o2"), test2};
    Button btn3 = {x + 24, y + 2, 14, SECONDARY_COLOR, STYLE_BORDERLESS, _T("setting.menu.o3"), test3};

    createMenu(x, y, width, (ColorRGB){0, 255, 0}, STYLE_DEFAULT, "setting.menu.label", &btn1, &btn2, &btn3);
}

void showSettingsPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLanguage();
    buttonClose();

    createText(ALIGN_CENTER, 10, _T("settings.visual.txt"), (ColorRGB){0, 255, 0});

    
    int width = (int)strlen(_T("setting.menu.o1")) +
                (int)strlen(_T("setting.menu.o2")) + 
                (int)strlen(_T("setting.menu.o3")) + 16;
    initMenu(columns, rows, width);
}