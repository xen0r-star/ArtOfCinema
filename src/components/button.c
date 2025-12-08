#include "button.h"


static Button buttons[MAX_BUTTONS];
static int button_count = 0;

static DataButton dataButtons[MAX_DATABUTTONS];
static int dataButton_count = 0;

static void drawButton(const Button *button) {
    if (button->style == STYLE_DEFAULT) {
        setColor(button->color);
        cursor(button->x, button->y);
        printf("\311");
        for (int j = 0; j < button->width - 2; j++) printf("\315");
        printf("\273");
    
        cursor(button->x, button->y + 1);
        printf("\272");

        setColor(button->color);
        cursor(button->x + button->width - 1, button->y + 1);
        printf("\272");
    
        cursor(button->x, button->y + 2);
        printf("\310");
        for (int j = 0; j < button->width - 2; j++) printf("\315");
        printf("\274");
    }

    cursor(button->x + (button->width - (int)strlen(button->label)) / 2, button->y + 1);

    if (button->style == STYLE_BORDERLESS)
        setColor(button->color);
    else
        setColor(COLOR_WHITE);

    printf("%s", button->label);
}

void createButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void)) {
    if (button_count >= MAX_BUTTONS) return;

    int columns, rows;
    sizeScreen(&columns, &rows);
    if (x && y) {
        if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, width);
        if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 3);
        buttons[button_count++] = (Button){x, y, width, color, style, label, onClick};
    } else {
        buttons[button_count++] = (Button){x, y, width, color, style, label, onClick};
        return;
    }
    drawButton(&buttons[button_count - 1]);
}

void createDataButton(int x, int y, int width, const char* label, Color color, Style style, void (*onClick)(void*), void* data) {
    if (dataButton_count >= MAX_DATABUTTONS) return;

    int columns, rows;
    sizeScreen(&columns, &rows);

    if (x > ALIGN_LIMIT) x = HorizontalAlignment(x, columns, width);
    if (y > ALIGN_LIMIT) y = VerticalAlignment(y, rows, 3);

    dataButtons[dataButton_count++] = (DataButton){x, y, width, color, style, label, onClick, data};
    drawButton((Button*)&dataButtons[dataButton_count - 1]);
}

// Button functions
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

// DataButton functions
int deleteButtonData(DataButton *button) {
    for (int i = 0; i < dataButton_count; i++) {
        if (&dataButtons[i] == button) {
            for (int j = i; j < dataButton_count - 1; j++) {
                dataButtons[j] = dataButtons[j + 1];
            }
            dataButton_count--;
            return 1;
        }
    }

    return 0;
}

void deleteAllDataButtons() {
    dataButton_count = 0;
}

DataButton *getDataButton(int index) {
    return &dataButtons[index];
}

int getDataButtonCount() {
    return dataButton_count;
}