#include "main.h"


static AppPage page = PAGE_DIRECTOR;
static AppPage previousPage = -1;

void resetPage(){
    deleteAllInputs();
    deleteAllButtons();
    deleteAllDataButtons();
    deleteAllMenus();
    clearScreen();
}


int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    
    initTranslation();

    while(1) {
        // Recuperer la taille de l'écran
        sizeScreen(&columns, &rows);

        // Si taille change OU changement de page
        if (columns != previousColumns || rows != previousRows || page != previousPage) {
            previousPage = page;

            resetPage();

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

                case PAGE_DIRECTOR_FILM:
                    showDirectorFilmPage();
                    break;

                case PAGE_DIRECTOR_SHOP:
                    showDirectorShopPage();
                    break;

                case PAGE_CLIENT:
                    showClientPage();
                    break;

                case PAGE_SETTINGS:
                    showSettingsPage();
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