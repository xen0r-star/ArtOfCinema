#include "footer.h"


void drawFooter() {
    int cols, rows;
    sizeScreen(&cols, &rows);
    cursor(2, rows - 1);
    setColor(COLOR_BRIGHT_BLACK);
    printf("Copyright %c2025 ArtOfCinema", (char)184);

    cursor(cols - (int)strlen(APP_VERSION), rows - 1);
    printf("%s", APP_VERSION);
}