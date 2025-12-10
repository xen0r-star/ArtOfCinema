#include "directorFilm.h"

static int pageIndex = 0;
static MovieNode *WaitingMovies = NULL;

static void addIdList(void *movie){
    Movie *mv = movie;
    int idP = &mv->id;

    MovieNode *curr = WaitingMovies;
    while (curr != NULL) {
        if (curr->movie->id == idP) {
            
            return;
        }
        curr = curr->next;
    }

    MovieNode *newNode = malloc(sizeof(MovieNode));
    if (newNode) {
        Movie *newPdt = malloc(sizeof(Movie));
        newPdt->id = idP;
        newNode->movie = newPdt;
        newNode->next = NULL;

        if (WaitingMovies == NULL) {
            WaitingMovies = newNode;
            
        } else {
            MovieNode *temp = WaitingMovies;
            while(temp->next != NULL) {
                temp = temp->next; 
            }
            temp->next = newNode;
        }
    }
}

static void prevPage(){
    if (pageIndex > 0){
        pageIndex--;
        setCurrentPage(PAGE_DIRECTOR_FILM);
    }
}

static void nextPage(){
    pageIndex++;
    setCurrentPage(PAGE_DIRECTOR_FILM);
}

static void initItem(int columns, int rows){
    int listStartY = 15;
    int itemHeight = 3;
    int maxItems = (rows - 3 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;

    MovieNode* node = getMovieList();

    int skipCount = pageIndex * maxItems;
    int skipped = 0;

    while (node != NULL && skipped < skipCount){
        node = node->next;
        skipped++;
    }

    int i = 0;
    while (i < maxItems && node != NULL){
        Movie *movie = getMovieById(node->movie->id);

        if (movie) {
            char id[6], duration[4];

            snprintf(id, sizeof(id), "%5d", node->movie->id);
            snprintf(duration, sizeof(duration), "%3d", node->movie->duration);

            createText(columns*0.12, listStartY + (i * itemHeight), id, COLOR_WHITE);
            createText(columns*0.20, listStartY + (i * itemHeight), node->movie->name, COLOR_WHITE);
            createText(columns*0.45, listStartY + (i * itemHeight), duration, COLOR_WHITE);
            
            createDataButton(columns*0.80, listStartY + (i * itemHeight) - 1, 5, "X", COLOR_RED, STYLE_DEFAULT, deleteMovie, node->movie);
            // createDataButton(columns*0.85, listStartY + (i * itemHeight) - 1, 5, "...", COLOR_BLUE, STYLE_DEFAULT, advancedProd, node->movie);
            // DANS "..." AJOUTER POSSIIBILITE DE RESERVER DE LA NOURRITURE
        }
        i++;
        node = node->next;
    }

    int startBtnX = (columns - (32)) / 2;
    if (pageIndex > 0)
        createButton(startBtnX, rows - 3, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
    else
        createButton(startBtnX, rows - 3, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

    if (node != NULL)
        createButton(startBtnX + 17, rows - 3, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
    else
        createButton(startBtnX + 17, rows - 3, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

}

void showDirectorFilmPage(){
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();

    createText(ALIGN_CENTER, 7, _T("director.f.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 9, _T("director.f.desc"), COLOR_WHITE);

    createDataButton(columns - 20, rows - 3, 20, _T("save"), COLOR_WHITE, STYLE_DEFAULT, saveMovie, &WaitingMovies);

    createMenu(ALIGN_CENTER, 11, columns*0.8, COLOR_GREEN, STYLE_DEFAULT, "director.f.tbl", NULL, NULL, NULL);

    buttonBack(PAGE_DIRECTOR);
    initItem(columns, rows);        // Initialisation + affichage du stock
}