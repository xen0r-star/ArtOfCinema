#include "setting.h"


static void goToSettings() {
    setSavePage(getCurrentPage());
    setCurrentPage(PAGE_SETTINGS);
}

void buttonSetting() {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    createButton(columns - 20, rows - 3, 20, _T("setting.btn.label"), SECONDARY_COLOR, STYLE_DEFAULT, goToSettings);
}
