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
#include "./pages/home.h"
#include "./pages/login.h"
#include "./pages/validelogin.h"
#include "./pages/nvalidelogin.h"
#include "./pages/signup.h"
#include "./pages/validesignup.h"
#include "./pages/nvalidesignup.h"
#include "./pages/director.h"
#include "./pages/directorfilm.h"
#include "./pages/directorshop.h"
#include "./pages/client.h"


#define APP_VERSION "v1.0.0"


typedef enum {
    PAGE_LOADING,
    PAGE_HOME,
    PAGE_LOGIN,
    PAGE_VALIDE_LOGIN,
    PAGE_NVALIDE_LOGIN,
    PAGE_SIGNUP,
    PAGE_VALIDE_SIGNUP,
    PAGE_NVALIDE_SIGNUP,
    PAGE_DIRECTOR,
    PAGE_DIRECTOR_FILM,
    PAGE_DIRECTOR_SHOP,
    PAGE_CLIENT,

    PAGE_EXIT
} AppPage;


AppPage getCurrentPage();
void setCurrentPage(AppPage newPage);

#endif