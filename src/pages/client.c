#include "home.h"

void printHELLO1() {
    cursor(10, 10);

    clearScreen();
    printf("Suite\n");

    Sleep(1000);

    setCurrentPage(PAGE_LOADING);
}

void showClientPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    // Dessine le logo
    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    createText(5, 10, "Votre Compte ARTOFCINEMA" , COLOR_GREEN, CENTER);
    createText(5 , 11, "Entrez votre email pour vous connecter ou creer un compte." , COLOR_WHITE, CENTER);
    
    createInput((columns - INPUT_WIDTH) / 2, 15, "Email", "exemple@artofcinema.be");
    createButton((columns - 21) / 2, rows - 7, 18, COLOR_GREEN, "CONTINUER", printHELLO1);

    // Dessine le footer
    drawFooter();
}
