#include "text.h"


void createText(int x, int y, const char *label, ColorRGB color) {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, strlen(label));
    if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 1);

    cursor(x, y);
    
    setColor(color);
    printf("%s ", label);
}