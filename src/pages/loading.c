#include "loading.h"

static void drawLoadingBar(int progressValue) {
    int columns, rows;
    sizeScreen(&columns, &rows);

    int progressWidth = (SIZE_LOADING_BAR * progressValue) / 100;
    int startX = (columns - SIZE_LOADING_BAR) / 2;
    int y = rows / 2 + 2;


    // Partie remplie
    cursor(startX, y);
    if (progressWidth <= 25)        setBackground((ColorRGB){255, 0, 0});
    else if (progressWidth <= 50)   setBackground((ColorRGB){255, 255, 0});
    else                            setBackground((ColorRGB){0, 255, 0});
    for (int i = 0; i < progressWidth; i++) printf(" ");


    // Partie vide
    setBackground((ColorRGB){255, 255, 255});
    cursor(startX + progressWidth, y);
    for (int i = progressWidth; i < SIZE_LOADING_BAR; i++) printf(" ");


    // Pourcentage
    char buffer[8];
    sprintf(buffer, "%3d%%", progressValue);

    int textX = columns / 2 - (int)strlen(buffer) / 2;

    for (int i = 0; i < (int)strlen(buffer); i++) {
        int charPos = textX + i;

        cursor(charPos, y);

        if (charPos < startX + progressWidth) {
            if (progressWidth <= 25)        setBackground((ColorRGB){255, 0, 0});
            else if (progressWidth <= 50)   setBackground((ColorRGB){255, 255, 0});
            else                            setBackground((ColorRGB){0, 255, 0});

        } else {
            setBackground((ColorRGB){255, 255, 255});
        }

        setColor((ColorRGB){0, 0, 0});
        printf("%c", buffer[i]);
    }

    resetColor();
}


void showLoadingScreen() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    drawVersionFooter();


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



    // Animation de chargement
    for (int i = 2; i <= 100; i += 2) {
        // Texte de chargement
        createText(ALIGN_CENTER, rows / 2, _T("loading"), SUCCESS_COLOR);

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
    createText(ALIGN_CENTER, rows / 2, _T("welcome"), PRIMARY_COLOR);

    Sleep(1500);


    setCurrentPage(PAGE_LOGIN);
}