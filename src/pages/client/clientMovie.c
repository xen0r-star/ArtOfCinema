#include "clientMovie.h"

static int pageIndex = 0;

static void prevPage() {
    if (pageIndex > 0) {
        pageIndex--;
        setCurrentPage(PAGE_CLIENT_MOVIE);
    }
}

static void nextPage() {
    pageIndex++;
    setCurrentPage(PAGE_CLIENT_MOVIE);
}


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


    int listStartY = 14;
    int itemHeight = 2;
    int maxItems = (rows - 6 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;

    ProjectionNode *node = getProjectionList();
    

    int skipCount = pageIndex * maxItems;
    int skipped = 0;
    while (node != NULL && skipped < skipCount) {
        node = node->next;
        skipped++;
    }

    int i = 0;
    while (i < maxItems && node != NULL) {
        Movie *movie = getMovieById(node->projection.movie_id);
        
        if (movie) {
            char str[16];
            snprintf(str, sizeof(str), "%4d places", node->projection.available_seats);

            createText(startLine, 
                listStartY + (i * itemHeight), 
                movie->name, COLOR_WHITE
            );
            createText(
                startLine + INPUT_WIDTH + 1, 
                listStartY + (i * itemHeight), 
                node->projection.datetime, COLOR_WHITE
            );
            createText(
                startLine + INPUT_WIDTH + 2 + 16 + 1, 
                listStartY + (i * itemHeight), 
                str, COLOR_WHITE
            );
        }

        i++;
        node = node->next;
    }


    int startBtnX = (columns - (15 + 2 + 15)) / 2;

    if (pageIndex > 0)
        createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
    else 
        createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
    
    if (node != NULL)
        createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
    else 
        createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
}