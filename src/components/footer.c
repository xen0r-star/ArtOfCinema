#include "footer.h"


void drawFooter() {
    int cols, rows;
    sizeScreen(&cols, &rows);
    cursor(2, rows - 1);
    setColor(TEXTSECONDARY_COLOR);
    printf("Copyright %c2025 ArtOfCinema", (char)184);
}

void drawVersionFooter() {
    int cols, rows;
    sizeScreen(&cols, &rows);

    setColor(TEXTSECONDARY_COLOR);
    cursor(cols - (int)strlen(APP_VERSION), rows - 1);
    printf("%s", APP_VERSION);
}