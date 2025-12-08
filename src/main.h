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

#include "./types/page.h"

#include "./pages/loading.h"
#include "./pages/login.h"
#include "./pages/director/director.h"
#include "./pages/client/client.h"
#include "./pages/client/clientMovie.h"
#include "./pages/client/clientReserve.h"
#include "./pages/client/clientFood.h"


#define APP_VERSION "v0.0.2"


AppPage getCurrentPage();
void setCurrentPage(AppPage newPage);
void refreshPage();

#endif