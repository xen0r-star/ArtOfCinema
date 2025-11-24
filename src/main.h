#ifndef MAIN_H
#define MAIN_H


#include <stdio.h>
#include <windows.h>

#include "./utils/screen.h"
#include "./components/logo.h"
#include "./components/input.h"
#include "./components/button.h"
#include "./components/footer.h"
#include "./events/event.h"

#include "./pages/loading.h"
#include "./pages/home.h"


#define APP_VERSION "v1.0.0"


typedef enum {
    PAGE_LOADING,
    PAGE_HOME,
    PAGE_LOGIN
} AppPage;


#endif