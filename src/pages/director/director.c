#include "director.h"

static void filmPage(){
    setCurrentPage(PAGE_DIRECTOR_FILM);
}

static void shopPage(){
    setCurrentPage(PAGE_DIRECTOR_SHOP);
}

void saveProduct(void *list) {
    ProductNode *pdt = (ProductNode*)list;
    saveProducts(pdt);
    shopPage();
}

void saveMovie(void *list) {
    MovieNode *mv = (MovieNode*)list;
    // saveProducts(mv);
    filmPage();
}

void showDirectorPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLogout();
    buttonLanguage();

 
    createText(ALIGN_CENTER, 10, _T("director.visual.lbl"), PRIMARY_COLOR);
    createText(ALIGN_CENTER, 12, _T("director.visual.desc"), TEXT_COLOR);
    createButton((columns-14)/2-10, 15, 14, _T("director.btn1"), TERTIARY_COLOR, STYLE_DEFAULT, filmPage);
    createButton((columns-14)/2+10, 15, 15, _T("director.btn2"), TERTIARY_COLOR, STYLE_DEFAULT, shopPage);
}