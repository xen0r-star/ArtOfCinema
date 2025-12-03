#include "client.h"


void showClientPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();

    createText(5, 10, _T("client.visual.txt") , COLOR_GREEN, CENTER);
}
