#include "client.h"


static void moviesPage() {
    setCurrentPage(PAGE_CLIENT_MOVIE);
}

static void foodPage() {
    setCurrentPage(PAGE_CLIENT_FOOD);
}

static void reservePage() {
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void quotePage() {
    setCurrentPage(PAGE_CLIENT_QUOTE);
}


void showClientPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonSetting();

    createText(ALIGN_CENTER, 10, _T("client.visual.txt"), PRIMARY_COLOR);
    createButton(ALIGN_CENTER, 12, 20, _T("client.btn.view.movies"),  TERTIARY_COLOR, STYLE_DEFAULT, moviesPage);
    createButton(ALIGN_CENTER, 15, 20, _T("client.btn.view.food"),    TERTIARY_COLOR, STYLE_DEFAULT, foodPage);
    createButton(ALIGN_CENTER, 18, 20, _T("client.btn.view.reserve"), TERTIARY_COLOR, STYLE_DEFAULT, reservePage);
    createButton(ALIGN_CENTER, 21, 20, _T("client.btn.view.quote"),   TERTIARY_COLOR, STYLE_DEFAULT, quotePage);
}