#include "back.h"


static void backPageHandler(void* data) {
    AppPage* page = (AppPage*)data;
    setCurrentPage(*page);
}

void buttonBack(AppPage page) {
    static AppPage targetPage;
    targetPage = page;
    createDataButton(1, ALIGN_TOP, 6, _T("return"), WARNING_COLOR, STYLE_BORDERLESS, backPageHandler, &targetPage);
}