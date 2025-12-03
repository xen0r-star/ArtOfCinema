#include "logout.h"


static void backToLogin() {
    resetUser();
    setCurrentPage(PAGE_LOGIN);
}

void buttonLogout() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    createButton(ALIGN_RIGHT, ALIGN_BOTTOM, 20, COLOR_RED, "DECONNEXION", backToLogin);
}