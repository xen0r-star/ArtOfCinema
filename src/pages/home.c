#include "home.h"

void printHELLO5() {
    cursor(10, 10);

    clearScreen();
    printf("Suite\n");
    setLanguage("en");
    Sleep(1000);

    setCurrentPage(PAGE_LOADING);
}

void switchLanguage(){
    const char* language = getLanguage();
    if((strcmp(language, "fr") == 0)){
        setLanguage("en");
        setCurrentPage(PAGE_LOADING);
        return;
    }
    if((strcmp(language, "en") == 0)){
        setLanguage("fr");
        setCurrentPage(PAGE_LOADING);
        return;
    }
}

void showHomePage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    // Dessine le logo
    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    createText(5, 10, _T("homemsg1") , COLOR_GREEN, CENTER);
    createText(5 , 11, _T("homemsg2") , COLOR_WHITE, CENTER);
    
    createInput((columns - INPUT_WIDTH) / 2, 15, _T("mail"), _T("mailexample"));
    createButton((columns - 21) / 2, rows - 7, 18, COLOR_GREEN, _T("homecontinuebtn"), printHELLO5);

    createButton(columns - 11, rows - 4, 8, COLOR_BLUE, _T("language"), switchLanguage);

    // Dessine le footer
    drawFooter();
}
