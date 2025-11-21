#include "cursor.h"


void cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}