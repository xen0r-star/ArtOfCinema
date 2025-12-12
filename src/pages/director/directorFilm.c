#include "directorFilm.h"

static int pageIndex = 0;

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

static void addFilm() {
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
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
            char id[20], duration[30], title[51];

            snprintf(id, sizeof(id), "ID : %5d", node->movie->id);
            snprintf(duration, sizeof(duration), "Temps : %3d minutes", node->movie->duration);
            snprintf(title, sizeof(title), "Titre : %s", node->movie->name);

            createText(columns * 0.12, listStartY + (i * itemHeight), id, TEXT_COLOR);
            createText(columns * 0.25, listStartY + (i * itemHeight), title, TEXT_COLOR);
            createText(columns * 0.65, listStartY + (i * itemHeight), duration, TEXT_COLOR);
            
            createDataButton(columns * 0.85, listStartY + (i * itemHeight) - 1, 5, "X", WARNING_COLOR, STYLE_DEFAULT, deleteMovie, node->movie);
        }
        i++;
        node = node->next;
    }

    int startBtnX = (columns - (32)) / 2;
    if (pageIndex > 0)
        createButton(startBtnX, rows - 3, 15, _T("prev"), TERTIARY_COLOR, STYLE_DEFAULT, prevPage);
    else
        createButton(startBtnX, rows - 3, 15, _T("prev"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);

    if (node != NULL)
        createButton(startBtnX + 17, rows - 3, 15, _T("next"), TERTIARY_COLOR, STYLE_DEFAULT, nextPage);
    else
        createButton(startBtnX + 17, rows - 3, 15, _T("next"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
    createButton(columns - 40, rows - 3, 16, _T("director.f.btn1"), SUCCESS_COLOR, STYLE_DEFAULT, addFilm);

}



void showDirectorFilmPage(){
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();

    createText(ALIGN_CENTER, 7, _T("director.f.lbl"), SUCCESS_COLOR);
    createText(ALIGN_CENTER, 9, _T("director.f.desc"), TEXT_COLOR);

    createMenu(ALIGN_CENTER, 11, columns*0.8, SUCCESS_COLOR, STYLE_DEFAULT, "director.f.tbl", NULL, NULL, NULL);

    buttonBack(PAGE_DIRECTOR);
    initItem(columns, rows);        // Initialisation + affichage des films
}