#include "main.h"



void printHELLO() {
    cursor(10, 10);

    // Ouvrir autre page
    clearScreen();
    printf("Suite\n");
}


int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    
    while(1) {
        // Recuperer la taille de l'ecrant
        sizeScreen(&columns, &rows);

        // Si taille change
        if (columns != previousColumns || rows != previousRows) {
            // Efface l'ecrant
            clearScreen();

            // Dessine le logo
            drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

            // Crée le button et le input
            createInput((columns - INPUT_WIDTH) / 2, 15, "Email", "exemple@artofcinema.com" , NULL);
            createButton((columns - 21) / 2, rows - 5, 21, COLOR_GREEN, "CONTINUER", printHELLO);

            // Dessine le footer
            drawFooter();
        }

        // Regarde les clics
        handleClick();

        // Met a jour les anciennes valeurs
        previousColumns = columns;
        previousRows = rows;
    }
    

    return 0;
}