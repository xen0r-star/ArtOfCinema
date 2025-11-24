#include "main.h"



int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    AppPage page = PAGE_LOADING, previousPage = -1;

    while(1) {
        // Recuperer la taille de l'écran
        sizeScreen(&columns, &rows);

        // Si taille change OU changement de page
        if (columns != previousColumns || rows != previousRows || page != previousPage) {
            previousPage = page;

            switch (page) {
                case PAGE_LOADING:
                    page = showLoadingScreen();
                    break;
                case PAGE_HOME:
                    page = showHomePage();
                    break;
            }
            
            // Met a jour les anciennes valeurs
            previousColumns = columns;
            previousRows = rows;
        }

        // Gere les evenements (ne redessine pas la page)
        // On appelle seulement inputEvent qui gère aussi les clicks généraux
        event();
        
        // Petite pause pour ne pas surcharger le CPU
        Sleep(10);
    }
    

    return 0;
}