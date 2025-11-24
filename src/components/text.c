#include "text.h"

Text texts[MAX_TEXTS];
int text_count = 0;

void createText(int x, int y, const char *label, Color color, const Align align) {
    if (text_count >= MAX_TEXTS) return;

    Text *text = &texts[text_count];

    text->x = x;
    text->y = y;

    // Initialise value avec calloc (met à zéro)
    text->label = (char*)calloc(TEXT_WIDTH, sizeof(char));
    if (text->label != NULL && label != NULL) {
        strncpy(text->label, label, TEXT_WIDTH - 1);
        text->label[TEXT_WIDTH - 1] = '\0'; // Sécurité
    }

    text->isFocused = 0;
    text_count++;

    // Vérification si couleur NULL ou existante. Par défaut Blanc
    // (color == NULL) ? setColor(color) : setColor(COLOR_WHITE);
    setColor(color);
    int columns, rows;
    sizeScreen(&columns, &rows);
    x = AlignmentOBJ(align, columns, label);
    cursor(x, y);
    printf("%s ", label);
}


int deleteText(Text *text) {
    for (int i = 0; i < text_count; i++) {
        if (&texts[i] == text) {
            if (texts[i].label)       free(texts[i].label);
            if (texts[i].color)       free(texts[i].color);

            for (int j = i; j < text_count - 1; j++) {
                texts[j] = texts[j + 1];
            }
            text_count--;
            return 1;
        }
    }

    return 0;
}

void deleteAllTexts() {
    for (int i = 0; i < text_count; i++) {
        if (texts[i].label) free(texts[i].label);
        if (texts[i].color) free(texts[i].color);
    }
    text_count = 0;
}

Text *getText(int index) {
    return &texts[index];
}

int getTextCount() {
    return text_count;
}


void redrawText(Text *text) {
    setColor(COLOR_WHITE);
    cursor(text->x + 2, text->y + 1);
    
    // Efface le contenu
    for(int i = 0; i < TEXT_WIDTH - 4; i++) printf(" ");
    cursor(text->x + 2, text->y + 1);
    
    // Affiche le contenu ou le placeholder
    // if (strlen(text->value) == 0) {
    //     setColor(COLOR_BRIGHT_BLACK);
    //     printf("%s", text->placeholder);
    // } else {
    //     setColor(COLOR_WHITE);
    //     printf("%s", text->value);
    // }
    
    // Affiche le curseur si focus
    if (text->isFocused) {
        printf("_");
    }
    
    resetColor();
    fflush(stdout);
}