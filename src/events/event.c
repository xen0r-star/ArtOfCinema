#include "event.h"


void event() {
    if (getInputCount() <= 0 && getButtonCount() <= 0) return;


    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    INPUT_RECORD rec;
    DWORD n;

    ReadConsoleInput(h, &rec, 1, &n);
    if (rec.EventType == MOUSE_EVENT) { // Detection souris
        int x = rec.Event.MouseEvent.dwMousePosition.X;
        int y = rec.Event.MouseEvent.dwMousePosition.Y;
        WORD bstate = rec.Event.MouseEvent.dwButtonState;

        if (bstate & FROM_LEFT_1ST_BUTTON_PRESSED) {
            // Click button
            for (int i = 0; i < getButtonCount(); i++) {
                Button *button = getButton(i);
                if (x >= button->x && x < button->x + button->width - 1 &&
                    y >= button->y && y < button->y + 3) {

                    cursorVisibility(0);
                    if (button->onClick) button->onClick();
                    return;
                }
            }

            // Click dataButton
            for (int i = 0; i < getDataButtonCount(); i++) {
                DataButton *button = getDataButton(i);
                if (x >= button->x && x < button->x + button->width - 1 &&
                    y >= button->y && y < button->y + 3) {

                    cursorVisibility(0);
                    if (button->onClick) button->onClick(button->data);
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
                            drawInputValue(input);
                        }
                    }

                    input->isFocused = 1;
                    // Redessine le nouvel input focusé
                    drawInputValue(input);
                    break;
                }
            }
        }

    } else if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown) { // Detection clavier
        // Regarder quel input est focus
        Input *input = NULL;
        for (int i = 0; i < getInputCount(); i++) {
            Input *inp = getInput(i);
            if (inp->isFocused) {
                input = inp;
                break;
            }
        }

        if (input != NULL) {
            char ch = rec.Event.KeyEvent.uChar.AsciiChar; // Récupère le caractère entré
            if (ch == 8) { // Touche effacer
                int len = strlen(input->value);
                if (len > 0) {
                    input->value[len - 1] = '\0'; // Supprime le dernier caractère
                }

            } else if (ch >= 32 && ch <= 126) { // Caractere imprimable
                int len = strlen(input->value);
                if (len < INPUT_WIDTH - 4) {
                    input->value[len] = ch; // Ajoute le caractère à la fin
                    input->value[len + 1] = '\0';
                }
            }

            drawInputValue(input);
        }
    }
}
