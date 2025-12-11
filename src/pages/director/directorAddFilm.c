#include "directorAddFilm.h"


static StepPage currentStep = STEP_PAGE_1;
static Movie newMovie;


static void cancelAction() {
    setCurrentPage(PAGE_DIRECTOR);
}

static void confirmStep1() {
    if (strcmp(getInput(0)->value, "") == 0 || 
        strcmp(getInput(1)->value, "") == 0
    ) {
        createText(ALIGN_CENTER, 9, "Veuillez remplir tous les champs", ERROR_COLOR);
        return;
    }

    newMovie.name = strdup(getInput(0)->value);
    newMovie.description = strdup(getInput(1)->value);
    currentStep = STEP_PAGE_2;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void confirmStep2() {
    if (strcmp(getInput(0)->value, "") == 0 ||
        strcmp(getInput(1)->value, "") == 0 ||
        strcmp(getInput(2)->value, "") == 0 ||
        strcmp(getInput(3)->value, "") == 0
    ) {
        createText(ALIGN_CENTER, 9, "Veuillez remplir tous les champs", ERROR_COLOR);
        return;
    }

    int duration = atoi(getInput(0)->value);
    int year = atoi(getInput(1)->value);

    if (duration < 0) duration = 0;
    if (year < 1800) year = 1800;
    if (year > 2999) year = 2999;

    newMovie.duration = duration;
    newMovie.year = year;
    newMovie.language = strdup(getInput(2)->value);
    newMovie.ageRating = strdup(getInput(3)->value);

    currentStep = STEP_PAGE_3;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void confirmStep3() {
    if (newMovie.cast_count == 0) {
        createText(ALIGN_CENTER, 9, "Veuillez ajouter au moins un acteur", ERROR_COLOR);
        return;
    }

    currentStep = STEP_PAGE_4;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void confirmStep4() {
    if (strcmp(getInput(0)->value, "") == 0 ||
        strcmp(getInput(1)->value, "") == 0
    ) {
        createText(ALIGN_CENTER, 9, "Veuillez remplir tous les champs", ERROR_COLOR);
        return;
    }

    int note = atoi(getInput(1)->value);
    if (note < 0) note = 0;
    if (note > 100) note = 100;

    newMovie.director = strdup(getInput(0)->value);
    newMovie.note = note;

    currentStep = STEP_PAGE_5;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void confirmStep5() {
    if (newMovie.type_count == 0) {
        createText(ALIGN_CENTER, 9, "Veuillez ajouter au moins un genre", ERROR_COLOR);
        return;
    }

    
    // add(newMovie) in file

    setCurrentPage(PAGE_DIRECTOR);
}


static void addActor() {
    if (strcmp(getInput(0)->value, "") == 0) {
        createText(ALIGN_CENTER, 9, "Veuillez entrer un nom d'acteur", ERROR_COLOR);
        return;
    }

    if (newMovie.cast_count >= 10) {
        createText(ALIGN_CENTER, 9, "Nombre maximum d'acteurs atteint", ERROR_COLOR);
        return;
    }

    newMovie.cast = realloc(newMovie.cast, sizeof(char*) * (newMovie.cast_count + 1));
    newMovie.cast[newMovie.cast_count] = strdup(getInput(0)->value);
    newMovie.cast_count++;

    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void addGenre() {
    if (strcmp(getInput(0)->value, "") == 0) {
        createText(ALIGN_CENTER, 9, "Veuillez entrer un genre", ERROR_COLOR);
        return;
    }

    if (newMovie.type_count >= 10) {
        createText(ALIGN_CENTER, 9, "Nombre maximum de genres atteint", ERROR_COLOR);
        return;
    }

    newMovie.types = realloc(newMovie.types, sizeof(char*) * (newMovie.type_count + 1));
    newMovie.types[newMovie.type_count] = strdup(getInput(0)->value);
    newMovie.type_count++;

    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}



void showDirectorAddFilmPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();
    buttonSetting();



    char str[32];
    snprintf(str, sizeof(str),  "Ajout d'un film - Etape %1d/5", currentStep + 1);
    createText(ALIGN_CENTER, 8, str, PRIMARY_COLOR);

    int centerX = columns / 2;


    if (currentStep == STEP_PAGE_1) {
        newMovie = (Movie){0};

        createInput(ALIGN_CENTER, 11, "Titre", "Entrez le titre");
        createInput(ALIGN_CENTER, 14, "Description", "Entrez la description");

        createButton(centerX + 1, rows - 6, 15, "Suivant", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep1);
        
    } else if (currentStep == STEP_PAGE_2) {
        createInput(ALIGN_CENTER, 11, "Duree (minutes)", "Entrez la duree");
        createInput(ALIGN_CENTER, 14, "Annee de sortie", "Entrez l'annee de sortie (xxxx)");
        createInput(ALIGN_CENTER, 17, "Langue", "Entrez la langue");
        createInput(ALIGN_CENTER, 20, "Classification d'age", "Entrez la classification d'age");

        createButton(centerX + 1, rows - 6, 15, "Suivant", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep2);

    } else if (currentStep == STEP_PAGE_3) {
        int startX = (columns - INPUT_WIDTH + 2 + 3) / 2;
        createInput(startX, 11, "Acteur", "Entrez le Acteur");
        createButton(startX + INPUT_WIDTH + 2, 11, 3, "+", TERTIARY_COLOR, STYLE_DEFAULT, addActor);

        for (int i = 0; i < newMovie.cast_count; i++) {
            createText(startX, 14 + i, newMovie.cast[i], TEXT_COLOR);
        }

        createButton(centerX + 1, rows - 6, 15, "Suivant", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep3);

    } else if (currentStep == STEP_PAGE_4) {
        createInput(ALIGN_CENTER, 11, "Directeur", "Entrez le nom du directeur");
        createInput(ALIGN_CENTER, 14, "Note", "Entrez la note (0-100)");
        createButton(centerX + 1, rows - 6, 15, "Suivant", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep4);

    } else if (currentStep == STEP_PAGE_5) {
        int startX = (columns - INPUT_WIDTH + 2 + 3) / 2;
        createInput(startX, 11, "Genre", "Entrez le genre");
        createButton(startX + INPUT_WIDTH + 2, 11, 3, "+", TERTIARY_COLOR, STYLE_DEFAULT, addGenre);

        for (int i = 0; i < newMovie.type_count; i++) {
            createText(startX, 14 + i, newMovie.types[i], TEXT_COLOR);
        }

        createButton(centerX + 1, rows - 6, 15, "Sauvegarder", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep5);
    }

    createButton(centerX - 16, rows - 6, 15, "Annuler", WARNING_COLOR, STYLE_DEFAULT, cancelAction);
}