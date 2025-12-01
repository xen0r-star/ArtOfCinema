#include "language.h"


static void switchLanguage(){
    const char* language = getLanguage();

    if(strcmp(language, "fr") == 0) {
        setLanguage("en");
        refreshPage();
        return;

    } else if(strcmp(language, "en") == 0) {
        setLanguage("fr");
        refreshPage();
        return;
    }
}

void buttonLanguage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    createButton(columns - 8, 1, 8, COLOR_CYAN, _T("login.btn.lge"), switchLanguage);
}