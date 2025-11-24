#include "loading.h"


void drawLoadingBar(int progressValue) {
    int columns, rows;
    sizeScreen(&columns, &rows);

    int progressWidth = (SIZE_LOADING_BAR * progressValue) / 100;
    int startX = (columns - SIZE_LOADING_BAR) / 2;
    int y = rows / 2 + 2;


    cursor(startX, y);
    if (progressWidth <= 25)        setBackground(BACKGROUND_COLOR_RED);
    else if (progressWidth <= 50)   setBackground(BACKGROUND_COLOR_YELLOW);
    else                            setBackground(BACKGROUND_COLOR_GREEN);
    for (int i = 0; i < progressWidth; i++) printf(" ");

    setBackground(BACKGROUND_COLOR_WHITE);
    cursor(startX + progressWidth, y);
    for (int i = progressWidth; i < SIZE_LOADING_BAR; i++) printf(" ");

    setColor(COLOR_BLACK);
    cursor(columns / 2 - 1, y);
    printf("%3d%%", progressValue);

    resetColor();
}


int showLoadingScreen() {
    clearScreen();
    int columns, rows;
    sizeScreen(&columns, &rows);

    // Dessine le logo
    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);


    // Bordure de la barre de chargement
    resetColor();
    cursor((columns - SIZE_LOADING_BAR - 3) / 2, rows / 2 + 1);
    printf("\311");
    for (int j = 0; j < SIZE_LOADING_BAR + 2; j++) printf("\315");
    printf("\273");

    cursor((columns - SIZE_LOADING_BAR - 3) / 2, rows / 2 + 2);
    printf("\272");

    cursor((columns + SIZE_LOADING_BAR + 2) / 2, rows / 2 + 2);
    printf("\272");

    cursor((columns - SIZE_LOADING_BAR - 3) / 2, rows / 2 + 3);
    printf("\310");
    for (int j = 0; j < SIZE_LOADING_BAR + 2; j++) printf("\315");
    printf("\274");

    // Dessine le footer
    drawFooter();


    // Animation de chargement
    for (int i = 1; i <= 100; i++) {
        // Texte de chargement
        setColor(COLOR_BRIGHT_GREEN);
        cursor((columns - 5) / 2, rows / 2);
        printf("Loading");

        int nbDots = (i / 10) % 4;
        for (int dot = 0; dot < nbDots; dot++)       printf(".");
        for (int space = nbDots; space < 3; space++) printf(" ");


        resetColor();
        drawLoadingBar(i);
        Sleep(25);
    }
    Sleep(800);


    clearScreen();
    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();

    // Message de bienvenue
    cursor((columns - 7) / 2, rows / 2);
    setColor(COLOR_BRIGHT_CYAN);
    printf("WELCOME!");

    Sleep(1500);


    return PAGE_HOME;
}