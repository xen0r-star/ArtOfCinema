#include "input.h"
#include "button.h"  // Inclure button.h pour accéder aux boutons


Input inputs[MAX_INPUTS];
int input_count = 0;

void createInput(int x, int y, const char *label, const char *placeholder, const char *value) {
    if (input_count >= MAX_INPUTS) return;


    Input *input = &inputs[input_count];

    input->x = x;
    input->y = y;
    input->label = (label != NULL) ? _strdup(label) : NULL;
    input->placeholder = (placeholder != NULL) ? _strdup(placeholder) : NULL;
    
    // Initialise value avec calloc (met à zéro)
    input->value = (char*)calloc(INPUT_WIDTH, sizeof(char));
    if (input->value != NULL && value != NULL) {
        strncpy(input->value, value, INPUT_WIDTH - 1);
        input->value[INPUT_WIDTH - 1] = '\0'; // Sécurité
    }
    
    input->isFocused = 0;
    input_count++;


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
        if (inputs[i].label) free(inputs[i].label);
        if (inputs[i].placeholder) free(inputs[i].placeholder);
        if (inputs[i].value) free(inputs[i].value);
    }
    input_count = 0;
}

Input *getInput(int index) {
    return &inputs[index];
}

int getInputCount() {
    return input_count;
}


void redrawInput(Input *input) {
    setColor(COLOR_WHITE);
    cursor(input->x + 2, input->y + 1);
    
    // Efface le contenu
    for(int i = 0; i < INPUT_WIDTH - 4; i++) printf(" ");
    cursor(input->x + 2, input->y + 1);
    
    // Affiche le contenu ou le placeholder
    if (strlen(input->value) == 0) {
        setColor(COLOR_BRIGHT_BLACK);
        printf("%s", input->placeholder);
    } else {
        setColor(COLOR_WHITE);
        printf("%s", input->value);
    }
    
    // Affiche le curseur si focus
    if (input->isFocused) {
        printf("_");
    }
    
    resetColor();
    fflush(stdout);
}