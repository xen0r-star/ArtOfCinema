#include "clientMovie.h"



void showClientMoviePage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();
    buttonBack(PAGE_CLIENT);


    int startLine = (columns - (INPUT_WIDTH + 16 + 10 + 4)) / 2;
    createInput(startLine, 10, "Recherche un film", "Titre du film...");
    createButton(startLine + INPUT_WIDTH + 2, 10, 16, "Rechercher", COLOR_CYAN, STYLE_DEFAULT, NULL);
    createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, 10, 10, "Trier", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

    int startBtnX = (columns - (15 + 2 + 15)) / 2;
    createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, NULL);
    createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, NULL);

    int i = 0;
    ProjectionNode *node = getProjectionList();
    while (14 + (i * 2) < rows - 6 && node != NULL) {
        Movie *movie = getMovieById(node->projection.movie_id);
        
        char str[16];
        snprintf(str, sizeof(str), "%4d places", node->projection.available_seats);

        createText(startLine, 
            14 + (i * 2), 
            movie->name, COLOR_WHITE
        );
        createText(
            startLine + INPUT_WIDTH + 1, 
            14 + (i * 2), 
            node->projection.datetime, COLOR_WHITE
        );
        createText(
            startLine + INPUT_WIDTH + 2 + 16 + 1, 
            14 + (i * 2), 
            str, COLOR_WHITE
        );

        i++;
        node = node->next;
    }
}