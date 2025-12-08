#include "main.h"


static AppPage page = PAGE_LOADING;
static AppPage previousPage = -1;


int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    
    initTranslation();
    loadMovies();
    loadProjections();
    loadProducts();

    while(1) {
        // Recuperer la taille de l'écran
        sizeScreen(&columns, &rows);

        // Si taille change OU changement de page
        if (columns != previousColumns || rows != previousRows || page != previousPage) {
            previousPage = page;

            deleteAllInputs();
            deleteAllButtons();
            deleteAllDataButtons();
            clearScreen();

            cursorVisibility(0);

            switch (page) {
                case PAGE_LOADING:
                    showLoadingScreen();
                    break;

                case PAGE_LOGIN:
                    showLoginPage();
                    break;

                case PAGE_DIRECTOR:
                    showDirectorPage();
                    break;

                case PAGE_CLIENT:
                    showClientPage();
                    break;

                case PAGE_CLIENT_MOVIE:
                    showClientMoviePage();
                    break;

                case PAGE_CLIENT_RESERVE:
                    showClientReservePage();
                    break;

                case PAGE_CLIENT_FOOD:
                    showClientFoodPage();
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
    previousPage = -1;
}

void refreshPage() {
    previousPage = -1;
}