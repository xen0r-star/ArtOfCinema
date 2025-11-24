#include "cursor.h"


void cursorVisibility(int visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    
    if (visible) cursorInfo.bVisible = TRUE;
    else cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(hOut, &cursorInfo);
}