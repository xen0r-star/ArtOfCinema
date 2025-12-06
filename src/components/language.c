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

    createButton(ALIGN_RIGHT, ALIGN_TOP, 8, TERTIARY_COLOR, _T("login.btn.lge"), switchLanguage);
}