#ifndef DIRECTOR_ADD_FILM_H
#define DIRECTOR_ADD_FILM_H


#include "../../components/logo.h"
#include "../../components/footer.h"
#include "../../components/text.h"
#include "../../components/button.h"
#include "../../components/input.h"


typedef enum StepPage {
    STEP_PAGE_1,
    STEP_PAGE_2,
    STEP_PAGE_3,
    STEP_PAGE_4,
    STEP_PAGE_5
} StepPage;

void showDirectorAddFilmPage();

#endif