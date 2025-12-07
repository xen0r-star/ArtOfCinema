#include "client.h"


static void testFunction() {
    // Placeholder for future functionality
}


void showClientPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();

    createText(ALIGN_CENTER, 10, _T("client.visual.txt"), COLOR_GREEN);
    createButton(ALIGN_CENTER, 12, 20, _T("client.btn.view.movies"),  COLOR_CYAN, STYLE_DEFAULT, testFunction);
    createButton(ALIGN_CENTER, 15, 20, _T("client.btn.view.food"),    COLOR_CYAN, STYLE_DEFAULT, testFunction);
    createButton(ALIGN_CENTER, 18, 20, _T("client.btn.view.reserve"), COLOR_CYAN, STYLE_DEFAULT, testFunction);
    createButton(ALIGN_CENTER, 21, 20, _T("client.btn.view.quote"),   COLOR_CYAN, STYLE_DEFAULT, testFunction);
}