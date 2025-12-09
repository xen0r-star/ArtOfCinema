#include "color.h"


void setColor(ColorRGB color) {
    printf("\x1b[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void setBackground(ColorRGB background) {
    printf("\x1b[48;2;%d;%d;%dm", background.r, background.g, background.b);
}

void resetColor() {
    printf("\033[0m");
}