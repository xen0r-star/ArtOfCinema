#include "text.h"


void createText(int x, int y, const char *label, ColorRGB  color) {
    int columns, rows;
    sizeScreen(&columns, &rows);
    
    if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, strlen(label));
    if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 1);

    if (x < 0) return;
    if (y < 0) return;
    if (x >= columns) return;
    if (y >= rows) return;


    cursor(x, y);
    
    setColor(color);
    printf("%s ", label);
}