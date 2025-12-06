#include "logo.h"


void drawLogo(int x, int y) {
    // Line 1
    cursor(x, y);
    setColor((ColorRGB){255, 0, 0});
    printf("    _         _    ");

    setColor((ColorRGB){255, 255, 255});
    printf("   ___   __  ");

    setColor((ColorRGB){255, 0, 0});
    printf("   ____ _                            ");


    // Line 2
    cursor(x, y + 1);
    setColor((ColorRGB){255, 0, 0});
    printf("   / \\   _ __| |_  ");

    setColor((ColorRGB){255, 255, 255});
    printf("  / _ \\ / _| ");

    setColor((ColorRGB){255, 0, 0});
    printf("  / ___(_)_ __   ___ _ __ ___   __ _ ");


    // Line 3
    cursor(x, y + 2);
    setColor((ColorRGB){255, 0, 0});
    printf("  / _ \\ | '__| __| ");

    setColor((ColorRGB){255, 255, 255});
    printf(" | | | | |_  ");

    setColor((ColorRGB){255, 0, 0});
    printf(" | |   | | '_ \\ / _ \\ '_ ` _ \\ / _` |");


    // Line 4
    cursor(x, y + 3);
    setColor((ColorRGB){255, 0, 0});
    printf(" / ___ \\| |  | |_  ");

    setColor((ColorRGB){255, 255, 255});
    printf(" | |_| |  _| ");

    setColor((ColorRGB){255, 0, 0});
    printf(" | |___| | | | |  __/ | | | | | (_| |");


    // Line 5
    cursor(x, y + 4);
    setColor((ColorRGB){255, 0, 0});
    printf("/_/   \\_\\_|   \\__| ");

    setColor((ColorRGB){255, 255, 255});
    printf("  \\___/|_|   ");

    setColor((ColorRGB){255, 0, 0});
    printf("  \\____|_|_| |_|\\___|_| |_| |_|\\__,_|");
}
