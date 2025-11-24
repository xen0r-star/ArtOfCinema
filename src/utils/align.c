#include "align.h"

int AlignmentOBJ(const Align align, const int columns, const char *test) {
    switch(align){
        case LEFT:
            return 1;
            break;

        case CENTER:
            return (columns - strlen(test)) / 2;
            break;
            
        case RIGHT:
            return columns + 1 - strlen(test);
            break;

        case DEF: // Comportement par défaut de l'alignement a réfléchir
            return 10;
            break;
    }
}