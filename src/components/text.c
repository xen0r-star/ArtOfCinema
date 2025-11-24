#include "text.h"


void createText(int x, int y, const char *label, Color color, const Align align) {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    x = AlignmentOBJ(align, columns, label);
    cursor(x, y);
    
    setColor(color);
    printf("%s ", label);
}