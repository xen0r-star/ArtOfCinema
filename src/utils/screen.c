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