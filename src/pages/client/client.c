#include "client.h"


void showClientPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();

    createText(5, 10, "COMPTE CLIENT" , COLOR_GREEN, CENTER);
}
