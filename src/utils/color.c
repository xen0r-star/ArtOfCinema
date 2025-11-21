#include "color.h"


void setColor(Color color) {
    printf("\033[%dm", color);
}

void resetColor() {
    printf("\033[0m");
}