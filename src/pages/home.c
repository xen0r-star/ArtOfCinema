#include "home.h"

void printHELLO() {
    cursor(10, 10);

    // Ouvrir autre page
    clearScreen();
    printf("Suite\n");
}

int showHomePage() {
    clearScreen();
    int columns, rows;
    sizeScreen(&columns, &rows);

    // Dessine le logo
    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    deleteAllInputs();
    deleteAllTexts();

    createText(5, 10, "Votre Compte ARTOFCINEMA" , COLOR_GREEN, CENTER);
    createText((columns - TEXT_WIDTH) / 2, 11, "ABC" , COLOR_GREEN, RIGHT);
    
    createInput((columns - INPUT_WIDTH) / 2, 15, "Email", "exemple@artofcinema.com" , NULL);
    createButton((columns - 21) / 2, rows - 5, 18, COLOR_GREEN, "CONTINUER", printHELLO);

    // Dessine le footer
    drawFooter();


    return PAGE_LOGIN;
}
