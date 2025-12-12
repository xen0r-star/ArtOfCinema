#include "directorAddFilm.h"


static StepPage currentStep = STEP_PAGE_1;
static Movie newMovie;
static ProjectionNode *newProjectionNode;
static ProjectionNode *tail = NULL;
static int nProj = 0;

static void cancelAction() {
    setCurrentPage(PAGE_DIRECTOR_FILM);
    currentStep = STEP_PAGE_1;
}

static void confirmStep1() {
    if (strcmp(getInput(0)->value, "") == 0 || 
        strcmp(getInput(1)->value, "") == 0 ||
        strcmp(getInput(2)->value, "") == 0
    ) {
        createText(ALIGN_CENTER, 9, "Veuillez remplir tous les champs", ERROR_COLOR);
        return;
    }

    float version = atoi(getInput(2)->value);
    if (version < 0.0) version = 1.0;
    if (version > 1000.0) version = 10.0;

    newMovie.name = strdup(getInput(0)->value);
    newMovie.description = strdup(getInput(1)->value);
    newMovie.version = version;
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
    currentStep = STEP_PAGE_6;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}

static void confirmStep6() {
    if (newProjectionNode == NULL) {
        createText(ALIGN_CENTER, 9, "Veuillez ajouter au moins une projection", ERROR_COLOR);
        return;
    }

    ProjectionNode *current = newProjectionNode;
    ProjectionNode *nextNode;

    while(current != NULL){
        nextNode =  current->next;

        Projection *tmpProjection = current->projection;
        
        addProjection(tmpProjection);

        free(current);

        current = nextNode;
    }

    newProjectionNode = NULL;

    currentStep = STEP_PAGE_1;
    addMovie(&newMovie);
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

bool is_bix(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static void addProj() {
    char *date = getInput(0)->value;
    char *time = getInput(1)->value;
    char *seats = getInput(2)->value;

    Projection *newProjection = NULL;

    if (date == NULL || strcmp(date, "") == 0) {
        createText(ALIGN_CENTER, 7, "Veuillez entrer une date de projection", ERROR_COLOR);
        return;
    }
    if (time == NULL || strcmp(time, "") == 0) {
        createText(ALIGN_CENTER, 7, "Veuillez entrer une heure de projection", ERROR_COLOR);
        return;
    }
    if (seats == NULL || strcmp(seats, "") == 0) {
        createText(ALIGN_CENTER, 7, "Veuillez entrer le nombre de places disponibles", ERROR_COLOR);
        return;
    }

    if (nProj >= 5) {
        createText(ALIGN_CENTER, 7, "Nombre maximum de projection atteint", ERROR_COLOR);
        return;
    }

    int day, month, year;
    if (strlen(date) != 10) {
        createText(ALIGN_CENTER, 7, "La date est incorrect", ERROR_COLOR);
        return;
    }

    int matchday = sscanf(date, "%d/%d/%d", &day, &month, &year);
    if (matchday != 3) {
        createText(ALIGN_CENTER, 7, "Le format de la date est incorrect", ERROR_COLOR);
        return;
    }

    if (month < 1 || month > 12 || year < 1900 || year > 3000) {
        createText(ALIGN_CENTER, 7, "Le mois ou l'annee sont invalides", ERROR_COLOR);
        return;
    }

    int days_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && is_bix(year)) {
        days_month[2] = 29;
    }

    if (day < 1 ||day > days_month[month]) {
        createText(ALIGN_CENTER, 7, "Le jour est invalide", ERROR_COLOR);
        return;
    }

    int hour, minute;

    if (strlen(time) != 5) {
        createText(ALIGN_CENTER, 7, "L heure est incorrect", ERROR_COLOR);
        return;
    }

    int matchtime = sscanf(time, "%d:%d", &hour, &minute);

    if (matchtime != 2) {
        createText(ALIGN_CENTER, 7, "Le format de l heure est incorrect", ERROR_COLOR);
        return;
    }

    if (hour < 0 || hour > 23) {
        createText(ALIGN_CENTER, 7, "L heure est invalide", ERROR_COLOR);
        return;
    }

    if (minute < 0 || minute > 59) {
        createText(ALIGN_CENTER, 7, "Les minutes sont invalides", ERROR_COLOR);
        return;
    }

    int available_seats = atoi(seats);

    if (available_seats < 0 || available_seats > 200) {
        createText(ALIGN_CENTER, 7, "Le nombre de sièges est invalides", ERROR_COLOR);
        return;
    }

    newProjection = calloc(1, sizeof(Projection));
    if (newProjection == NULL) {
        createText(ALIGN_CENTER, 7, "ERREUR DALLOC", ERROR_COLOR);
        return;
    }
    
    newProjection->datetime = (char *)malloc(strlen(date) + 1 + strlen(time) + 1);

    if (newProjection->datetime == NULL) {
        createText(ALIGN_CENTER, 7, "ERREUR DALLOC DATE", ERROR_COLOR);
        free(newProjection);
        return;
    }

    newProjection->movie_id = getNMovie() + 1;
    sprintf(newProjection->datetime, "%s %s", date, time);
    newProjection->available_seats = available_seats;
    
    // Create and append Node
    ProjectionNode *newNode = malloc(sizeof(ProjectionNode));
    if (newNode == NULL) {
        createText(ALIGN_CENTER, 7, "ERREUR DALLOC NEWNODE", ERROR_COLOR);
        free(newProjection->datetime);
        free(newProjection);
        return;
    }
    newNode->projection = newProjection;
    newNode->next = NULL;

    if (newProjectionNode == NULL) {
        newProjectionNode = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    nProj++;
    setCurrentPage(PAGE_DIRECTOR_ADD_FILM);
}


void showDirectorAddFilmPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();
    buttonSetting();



    char str[32];
    snprintf(str, sizeof(str),  "Ajout d'un film - Etape %1d/6", currentStep + 1);
    createText(ALIGN_CENTER, 6, str, PRIMARY_COLOR);

    int centerX = columns / 2;


    if (currentStep == STEP_PAGE_1) {
        newMovie = (Movie){0};

        createInput(ALIGN_CENTER, 11, "Titre", "Entrez le titre");
        createInput(ALIGN_CENTER, 14, "Description", "Entrez la description");
        createInput(ALIGN_CENTER, 17, "Version", "Entrez la version");

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
        createButton(centerX + 1, rows - 6, 15, "Suivant", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep5);
    } else if (currentStep == STEP_PAGE_6) {
        int startX = (columns - INPUT_WIDTH + 2 + 3) / 2;
        createInput(startX, 9, "Date", "Entrez la date de projection");
        createInput(startX, 12, "Heure", "Entrez l heure de projection");
        createInput(startX, 15, "Places", "Entrez le nombre de place disponible");

        createButton(startX + INPUT_WIDTH + 2, 15, 3, "+", TERTIARY_COLOR, STYLE_DEFAULT, addProj);

        ProjectionNode *current = newProjectionNode;
        int i = 0;
        while (current != NULL) {
            Projection *tempProjection = current->projection;
            char text[100];

            sprintf(text, "%s - %d places disponibles", tempProjection->datetime, tempProjection->available_seats);
            createText(startX, 17 + i, text, TEXT_COLOR);
            current = current->next;
            i++;
        }

        createButton(centerX + 1, rows - 6, 15, "Sauvegarder", SUCCESS_COLOR, STYLE_DEFAULT, confirmStep6);
    }

    createButton(centerX - 16, rows - 6, 15, "Annuler", WARNING_COLOR, STYLE_DEFAULT, cancelAction);
}