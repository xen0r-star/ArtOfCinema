#include "director.h"

void showDirectorPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();


    createText(5, 10, "COMPTE DIRECTEUR" , COLOR_GREEN, CENTER);
}
