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

    // Supprime les anciens inputs/buttons avant d'en créer de nouveaux
    deleteAllInputs();
    
    // Crée le button et le input
    createInput((columns - INPUT_WIDTH) / 2, 15, "Email", "exemple@artofcinema.com" , NULL);
    createButton((columns - 21) / 2, rows - 5, 18, COLOR_GREEN, "CONTINUER", printHELLO);

    // Dessine le footer
    drawFooter();


    return PAGE_LOGIN;
}
