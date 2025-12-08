#include "clientMovie.h"

static int pageIndex = 0;
static char filterTitle[100] = "";

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

static void onSearch() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterTitle, input->value);
        pageIndex = 0;
        setCurrentPage(PAGE_CLIENT_MOVIE);
    }
}




void showClientMoviePage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    if (rows > 40) drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    drawFooter();
    buttonLogout();
    buttonLanguage();
    buttonBack(PAGE_CLIENT);


    filterTitle[0] = '\0';

    int listStartY = 8;
    if (rows > 40) listStartY = 14;

    int itemHeight = 2;
    int maxItems = (rows - 6 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;
    
    
    int startLine = (columns - (INPUT_WIDTH + 16 + 10 + 4)) / 2;
    createInput(startLine, listStartY - 4, "Recherche un film", "Titre du film...");
    createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, "Rechercher", COLOR_CYAN, STYLE_DEFAULT, onSearch);
    createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, "Trier", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);


    ProjectionNode *node = getProjectionList();
    
    int matchesCount = 0;
    int displayedCount = 0;
    int skipCount = pageIndex * maxItems;
    int hasMore = 0;

    while (node != NULL) {
        Movie *movie = getMovieById(node->projection.movie_id);
        
        if (movie && searchMovieByName(movie->name, filterTitle)) {
            
            if (matchesCount >= skipCount) {
                if (displayedCount < maxItems) {
                    char str[16];
                    snprintf(str, sizeof(str), "%4d places", node->projection.available_seats);

                    createText(startLine, 
                        listStartY + (displayedCount * itemHeight), 
                        movie->name, COLOR_WHITE
                    );
                    createText(
                        startLine + INPUT_WIDTH + 1, 
                        listStartY + (displayedCount * itemHeight), 
                        node->projection.datetime, COLOR_WHITE
                    );
                    createText(
                        startLine + INPUT_WIDTH + 2 + 16 + 1, 
                        listStartY + (displayedCount * itemHeight), 
                        str, COLOR_WHITE
                    );
                    displayedCount++;

                } else {
                    hasMore = 1;
                    break;
                }
            }
            matchesCount++;
        }
        node = node->next;
    }


    int startBtnX = (columns - (15 + 2 + 15)) / 2;

    if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
    else               createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
    
    if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
    else         createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
}