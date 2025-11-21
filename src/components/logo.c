#include "logo.h"


void drawLogo(int x, int y) {
    // Line 1
    cursor(x, y);
    setColor(COLOR_RED);
    printf("    _         _    ");

    setColor(COLOR_WHITE);
    printf("   ___   __  ");

    setColor(COLOR_RED);
    printf("   ____ _                            ");


    // Line 2
    cursor(x, y + 1);
    setColor(COLOR_RED);
    printf("   / \\   _ __| |_  ");

    setColor(COLOR_WHITE);
    printf("  / _ \\ / _| ");

    setColor(COLOR_RED);
    printf("  / ___(_)_ __   ___ _ __ ___   __ _ ");


    // Line 3
    cursor(x, y + 2);
    setColor(COLOR_RED);
    printf("  / _ \\ | '__| __| ");

    setColor(COLOR_WHITE);
    printf(" | | | | |_  ");

    setColor(COLOR_RED);
    printf(" | |   | | '_ \\ / _ \\ '_ ` _ \\ / _` |");


    // Line 4
    cursor(x, y + 3);
    setColor(COLOR_RED);
    printf(" / ___ \\| |  | |_  ");

    setColor(COLOR_WHITE);
    printf(" | |_| |  _| ");

    setColor(COLOR_RED);
    printf(" | |___| | | | |  __/ | | | | | (_| |");


    // Line 5
    cursor(x, y + 4);
    setColor(COLOR_RED);
    printf("/_/   \\_\\_|   \\__| ");

    setColor(COLOR_WHITE);
    printf("  \\___/|_|   ");

    setColor(COLOR_RED);
    printf("  \\____|_|_| |_|\\___|_| |_| |_|\\__,_|");
}
