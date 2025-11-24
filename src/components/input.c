#include "input.h"


static Input inputs[MAX_INPUTS];
static int input_count = 0;


void createInput(int x, int y, const char *label, const char *placeholder) {
    if (input_count >= MAX_INPUTS) return;

    // Enregistre l'input
    Input *input = &inputs[input_count++];

    input->x = x;
    input->y = y;
    input->label = label ? _strdup(label) : NULL;
    input->placeholder = placeholder ? _strdup(placeholder) : NULL;
    
    input->value = calloc(INPUT_WIDTH, 1); // Initialise la valeur à une chaîne vide
    input->isFocused = 0;


    // Dessine l'input
    setColor(COLOR_WHITE);
    cursor(x, y);
    printf("\311\315 ");
    printf("%s ", label);
    for (int j = 0; j < INPUT_WIDTH - (int)strlen(label) - 5; j++) printf("\315");
    printf("\273");

    cursor(x, y + 1);
    printf("\272");
    cursor(x + 2, y + 1);
    setColor(COLOR_BRIGHT_BLACK);
    printf("%s", placeholder);
    setColor(COLOR_WHITE);
    cursor(x + INPUT_WIDTH - 1, y + 1);
    printf("\272");

    cursor(x, y + 2);
    printf("\310");
    for (int j = 0; j < INPUT_WIDTH - 2; j++) printf("\315");
    printf("\274");
}

void drawInputValue(Input *input) {
    cursorVisibility(0);

    int len = 0;
    int max_len = INPUT_WIDTH - 3; // Espace disponible avant la bordure
    
    // Affiche le contenu ou le placeholder
    cursor(input->x + 2, input->y + 1);
    if (strlen(input->value) == 0) {
        setColor(COLOR_BRIGHT_BLACK);
        printf("%s", input->placeholder);
        len += strlen(input->placeholder);
        
    } else {
        setColor(COLOR_WHITE);
        printf("%s", input->value);
        len += strlen(input->value);
    }

    // Efface seulement la fin pour éviter les textes cligniotants
    for(int i = len; i < max_len; i++) {
        printf(" ");
    }

    resetColor();
    
    // Positionne et affiche le curseur
    if (input->isFocused) {
        int textLen = strlen(input->value);
        cursor(input->x + 2 + textLen, input->y + 1);
        cursorVisibility(1);
    }
}



int deleteInput(Input *input) {
    for (int i = 0; i < input_count; i++) {
        if (&inputs[i] == input) {
            if (inputs[i].label)       free(inputs[i].label);
            if (inputs[i].placeholder) free(inputs[i].placeholder);
            if (inputs[i].value)       free(inputs[i].value);
            

            for (int j = i; j < input_count - 1; j++) {
                inputs[j] = inputs[j + 1];
            }
            input_count--;
            return 1;
        }
    }

    return 0;
}

void deleteAllInputs() {
    for (int i = 0; i < input_count; i++) {
        if (inputs[i].label)       free(inputs[i].label);
        if (inputs[i].placeholder) free(inputs[i].placeholder);
        if (inputs[i].value)       free(inputs[i].value);
    }
    input_count = 0;
}

Input *getInput(int index) {
    return &inputs[index];
}

int getInputCount() {
    return input_count;
}