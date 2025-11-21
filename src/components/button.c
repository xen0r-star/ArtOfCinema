#include "button.h"


Button buttons[MAX_BUTTONS];
int button_count = 0;


void createButton(int x, int y, int width, Color color, char *label, void (*onClick)(void)) {
    if (button_count >= MAX_BUTTONS) return;
    buttons[button_count++] = (Button){x, y, width, color, label, onClick};

    setColor(color);
    cursor(x, y);
    printf("\311");
    for (int j = 0; j < width - 2; j++) printf("\315");
    printf("\273");

    cursor(x, y + 1);
    printf("\272");
    cursor(x + (width - (int)strlen(label)) / 2, y + 1);
    
    setColor(COLOR_WHITE);
    printf("%s", label);
    setColor(color);
    cursor(x + width - 1, y + 1);
    printf("\272");

    cursor(x, y + 2);
    printf("\310");
    for (int j = 0; j < width - 2; j++) printf("\315");
    printf("\274");
}


int deleteButton(Button *button) {
    for (int i = 0; i < button_count; i++) {
        if (&buttons[i] == button) {
            for (int j = i; j < button_count - 1; j++) {
                buttons[j] = buttons[j + 1];
            }
            button_count--;
            return 1;
        }
    }

    return 0;
}

void deleteAllButtons() {
    button_count = 0;
}


void handleClick() {
    if (button_count <= 0) return;

    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    INPUT_RECORD rec;
    DWORD n;

    ReadConsoleInput(h, &rec, 1, &n);
    if (rec.EventType == MOUSE_EVENT) {
        int x = rec.Event.MouseEvent.dwMousePosition.X;
        int y = rec.Event.MouseEvent.dwMousePosition.Y;
        WORD bstate = rec.Event.MouseEvent.dwButtonState;

        if (bstate & FROM_LEFT_1ST_BUTTON_PRESSED) {
            for (int i = 0; i < button_count; i++) {
                Button *b = &buttons[i];
                if (x >= b->x && x < b->x + b->width &&
                    y >= b->y && y < b->y + 3) {
                    if (b->onClick) b->onClick();
                    return;
                }
            }
        }
    }
}