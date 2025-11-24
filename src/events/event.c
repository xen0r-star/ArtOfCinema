#include "event.h"


void event() {
    if (getInputCount() <= 0 && getButtonCount() <= 0) return;


    // Detection click souris
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
            // Click button
            for (int i = 0; i < getButtonCount(); i++) {
                Button *button = getButton(i);
                if (x >= button->x && x < button->x + button->width &&
                    y >= button->y && y < button->y + 3) {
                    if (button->onClick) button->onClick();
                    return;
                }
            }

            // Click input
            for (int i = 0; i < getInputCount(); i++) {
                Input *input = getInput(i);
                if (x >= input->x && x < input->x + INPUT_WIDTH &&
                    y >= input->y && y < input->y + 3) {

                    // Défocus tous les inputs et redessine
                    for (int j = 0; j < getInputCount(); j++) {
                        Input *input = getInput(j);
                        if (input->isFocused) {
                            input->isFocused = 0;

                            // Redessine l'ancien input focusé
                            redrawInput(input);
                        }
                    }

                    input->isFocused = 1;
                    // Redessine le nouvel input focusé
                    redrawInput(input);
                    break;
                }
            }
        }
    }



    // Detection clavier
    Input *input = NULL;
    for (int i = 0; i < getInputCount(); i++) {
        Input *inp = getInput(i);
        if (inp->isFocused) {
            input = inp;
            break;
        }
    }
    if (input == NULL) return;

    // Le kbhit() retour cassiment toujours 0
    if (kbhit()) {
        char ch = getch();
        if (ch == 8) { // Touche effacer
            int len = strlen(input->value);
            if (len > 0) {
                input->value[len - 1] = '\0';
            }

        } else if (ch >= 32 && ch <= 126) { // Caractere imprimable
            int len = strlen(input->value);
            if (len < INPUT_WIDTH - 4) {
                input->value[len] = ch;
                input->value[len + 1] = '\0';
            }
        }

        redrawInput(input);
    }
}
