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
#include "./core/movie.h"
#include "./core/projection.h"
#include "./core/product.h"
#include "./core/reservation.h"

#include "./types/page.h"

#include "./pages/loading.h"
#include "./pages/login.h"
#include "./pages/settings.h"
#include "./pages/credit.h"

#include "./pages/director/director.h"
#include "./pages/director/directorFilm.h"
#include "./pages/director/directorShop.h"
#include "./pages/director/directorAddFilm.h"

#include "./pages/client/client.h"
#include "./pages/client/clientMovie.h"
#include "./pages/client/clientReserve.h"
#include "./pages/client/clientFood.h"
#include "./pages/client/clientQuote.h"


#define APP_VERSION "v0.0.2"


AppPage getCurrentPage();
void resetPage();
void setCurrentPage(AppPage newPage);
void refreshPage();
AppPage getSavePage();
void setSavePage(AppPage newPage);


#endif