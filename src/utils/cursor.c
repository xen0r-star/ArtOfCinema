#include "cursor.h"


void cursor(int x, int y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x - 1, (SHORT)y };
    SetConsoleCursorPosition(h, pos);
}

void cursorVisibility(int visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    
    if (visible) cursorInfo.bVisible = TRUE;
    else cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(hOut, &cursorInfo);
}