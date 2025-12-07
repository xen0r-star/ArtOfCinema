#include "screen.h"


int sizeScreen(int *columns, int *rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return 0;
    }
    
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 1;
}

void clearScreen() {
    DWORD n;
    DWORD size;
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(h, &csbi);
    size = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(h, ' ', size, coord, &n);
    FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

    SetConsoleCursorPosition(h, coord);
}

void cursor(int x, int y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x - 1, (SHORT)y };
    SetConsoleCursorPosition(h, pos);
}

void hideCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = 0;
    SetConsoleCursorInfo(h, &info);
}

void showCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = 1;
    SetConsoleCursorInfo(h, &info);
}


void setColor(Color color) {
    printf("\033[%dm", color);
}

void setBackground(Background background) {
    printf("\033[%dm", background);
}

void resetColor() {
    printf("\033[0m");
}