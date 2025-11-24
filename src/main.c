#include "main.h"


static AppPage page = PAGE_LOADING;

int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    AppPage previousPage = -1;

    while(1) {
        // Recuperer la taille de l'écran
        sizeScreen(&columns, &rows);

        // Si taille change OU changement de page
        if (columns != previousColumns || rows != previousRows || page != previousPage) {
            previousPage = page;

            deleteAllInputs();
            deleteAllButtons();
            clearScreen();

            cursorVisibility(0);

            switch (page) {
                case PAGE_LOADING:
                    showLoadingScreen();
                    break;

                case PAGE_HOME:
                    showHomePage();
                    break;

                case PAGE_LOGIN:
                    showHomePage();
                    break;

                case PAGE_VALIDE_LOGIN:
                    showHomePage();
                    break;

                case PAGE_NVALIDE_LOGIN:
                    showHomePage();
                    break;

                case PAGE_SIGNUP:
                    showHomePage();
                    break;

                case PAGE_VALIDE_SIGNUP:
                    showHomePage();
                    break;

                case PAGE_DIRECTOR:
                    showHomePage();
                    break;

                case PAGE_DIRECTOR_FILM:
                    showHomePage();
                    break;

                case PAGE_DIRECTOR_SHOP:
                    showHomePage();
                    break;

                case PAGE_CLIENT:
                    showHomePage();
                    break;

                case PAGE_EXIT: 
                    return 0;
            }
            
            // Met a jour les anciennes valeurs
            previousColumns = columns;
            previousRows = rows;
        }

        event();
    }
    

    return 0;
}


AppPage getCurrentPage() {
    return page;
}

void setCurrentPage(AppPage newPage) {
    page = newPage;
}