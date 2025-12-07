#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <windows.h>

#include "./utils/screen.h"
#include "./utils/align.h"

#include "./components/logo.h"
#include "./components/text.h"
#include "./components/input.h"
#include "./components/button.h"
#include "./components/footer.h"

#include "./events/event.h"

#include "./i18n/translation.h"

#include "./pages/loading.h"
#include "./pages/login.h"
#include "./pages/director/director.h"
#include "./pages/director/directorFilm.h"
#include "./pages/director/directorShop.h"

#include "./pages/client/client.h"
#include "./pages/settings.h"


#define APP_VERSION "v0.0.2"


typedef enum {
    PAGE_LOADING,
    PAGE_LOGIN,
    PAGE_DIRECTOR,
    PAGE_DIRECTOR_FILM,
    PAGE_DIRECTOR_SHOP,
    PAGE_CLIENT,
    PAGE_SETTINGS,
    PAGE_EXIT
} AppPage;


AppPage getCurrentPage();
void resetPage();
void setCurrentPage(AppPage newPage);
void refreshPage();

#endif