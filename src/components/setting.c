#include "setting.h"


static void goToSettings() {
    resetUser();
    setCurrentPage(PAGE_SETTINGS);
}

static void backToLogin() {
    resetUser();
    setCurrentPage(PAGE_LOGIN);
}

void buttonSetting() {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    createButton(columns - 20, rows - 3, 20, _T("setting.btn.label"), COLOR_WHITE, STYLE_DEFAULT, goToSettings);
}

void buttonClose() {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    createButton(columns - 20, rows - 3, 20, _T("setting.btn.close"), COLOR_WHITE, STYLE_DEFAULT, backToLogin);
}
