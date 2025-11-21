#include "input.h"


void createInput(int x, int y, const char *label, const char *placeholder, const char *value) {
    setColor(COLOR_WHITE);
    cursor(x, y);
    printf("\311\315 ");
    printf("%s ", label);
    for (int j = 0; j < INPUT_WIDTH - (int)strlen(label) - 5; j++) printf("\315");
    printf("\273");

    cursor(x, y + 1);
    printf("\272");
    cursor(x + 2, y + 1);
    setColor(COLOR_BRIGHT_BLACK);
    printf("%s", placeholder);
    setColor(COLOR_WHITE);
    cursor(x + INPUT_WIDTH - 1, y + 1);
    printf("\272");

    cursor(x, y + 2);
    printf("\310");
    for (int j = 0; j < INPUT_WIDTH - 2; j++) printf("\315");
    printf("\274");
}