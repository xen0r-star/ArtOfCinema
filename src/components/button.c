#include "button.h"


static Button buttons[MAX_BUTTONS];
static int button_count = 0;


void createButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void)) {
    if (button_count >= MAX_BUTTONS) return;

    int columns, rows;
    sizeScreen(&columns, &rows);

    if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, width);
    if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 3);

    buttons[button_count++] = (Button){x, y, width, color, style, label, onClick};


    if (style == STYLE_DEFAULT) {
        setColor(color);
        cursor(x, y);
        printf("\311");
        for (int j = 0; j < width - 2; j++) printf("\315");
        printf("\273");
    
        cursor(x, y + 1);
        printf("\272");

        setColor(color);
        cursor(x + width - 1, y + 1);
        printf("\272");
    
        cursor(x, y + 2);
        printf("\310");
        for (int j = 0; j < width - 2; j++) printf("\315");
        printf("\274");
    }

    cursor(x + (width - (int)strlen(label)) / 2, y + 1);
    setColor(COLOR_WHITE);
    printf("%s", label);
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

Button *getButton(int index) {
    return &buttons[index];
}

int getButtonCount() {
    return button_count;
}