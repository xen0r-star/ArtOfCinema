#include "directorFilm.h"

static idMovieList *idList = NULL;

void showDirectorFilmPage(){
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();

    createText(ALIGN_CENTER, 10, _T("director.f.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 12, _T("director.f.desc"), COLOR_WHITE);

    createDataButton(columns - 20, rows - 3, 20, _T("save"), COLOR_WHITE, STYLE_DEFAULT, backToDashboard, &idList);
}