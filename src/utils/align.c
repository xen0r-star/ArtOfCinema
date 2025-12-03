#include "align.h"

int HorizontalAlignment(const HorizontalAlign align, const int columns, const int size) {
    switch(align){
        case ALIGN_LEFT:
            return 0;
            break;

        case ALIGN_CENTER:
            return (columns - size) / 2;
            break;
            
        case ALIGN_RIGHT:
            return columns - size;
            break;

        default:
            return align;
    }
}

int VerticalAlignment(const VerticalAlign align, const int rows, const int size) {
    switch(align){
        case ALIGN_TOP:
            return 0;
            break;

        case ALIGN_MIDDLE:
            return (rows - size) / 2;
            break;
            
        case ALIGN_BOTTOM:
            return rows - size;
            break;

        default:
            return align;
    }
}