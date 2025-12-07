#include "director.h"

static void resetScreen(){
    deleteAllInputs();
    deleteAllButtons();
    clearScreen();
}

static void backToDashboard() {
    resetScreen();
    showDirectorPage();
}


/* TEST */

static void showInfo(void *data){
    // resetScreen();
    // cursor(2,2);
    int value = *((int*)data);
    printf("Le bouton contient : %d\n", value);
}
/* TEST */


static void showStockManage(){
    resetScreen();
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    
    createMenu(ALIGN_CENTER, ALIGN_CENTER, 40, COLOR_GREEN, STYLE_DEFAULT, "director.s.tbl", NULL, NULL, NULL);
    // Init stock
    // Affichage stock actuel

    static int caca = 50;
    createDataButton((columns-14)/2+10, 15, 15, "TEST", COLOR_GREEN, STYLE_DEFAULT, showInfo, &caca);
    
    createButton(columns - 20, rows - 3, 20, _T("return"), COLOR_WHITE, STYLE_DEFAULT, showDirectorShopPage);

}

static void showReservF(){

}

static void showDirectorFilmPage(){
    resetScreen();
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();

    createText(ALIGN_CENTER, 10, _T("director.f.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 12, _T("director.f.desc"), COLOR_WHITE);

    createButton(columns - 20, rows - 3, 20, _T("return"), COLOR_WHITE, STYLE_DEFAULT, backToDashboard);
}

static void showDirectorShopPage(){
    resetScreen();
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();

    createText(ALIGN_CENTER, 10, _T("director.s.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 12, _T("director.s.desc"), COLOR_WHITE);
    createButton((columns-14)/2-10, 15, 14, _T("director.s.btn1"), COLOR_GREEN, STYLE_DEFAULT, showStockManage);
    createButton((columns-14)/2+10, 15, 15, _T("director.s.btn2"), COLOR_GREEN, STYLE_DEFAULT, showReservF);
    createButton(columns - 20, rows - 3, 20, _T("return"), COLOR_WHITE, STYLE_DEFAULT, backToDashboard);
}

void showDirectorPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();


    createText(ALIGN_CENTER, 10, _T("director.visual.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 12, _T("director.visual.desc"), COLOR_WHITE);
    createButton((columns-14)/2-10, 15, 14, _T("director.btn1"), COLOR_GREEN, STYLE_DEFAULT, showDirectorFilmPage);
    createButton((columns-14)/2+10, 15, 15, _T("director.btn2"), COLOR_GREEN, STYLE_DEFAULT, showDirectorShopPage);
    
    

}
