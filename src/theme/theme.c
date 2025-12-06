#include "theme.h"

ThemeID currentTheme = THEME_DEFAULT;
Theme THEMES[] = {
    [THEME_DEFAULT] = {
        .primary       = { 52, 152, 219 },
        .secondary     = { 255, 255, 255 },
        .tertiary      = { 236, 240, 241 },
        .background    = { 236, 240, 241 },

        .text          = { 44, 62, 80 },
        .textSecondary = { 127, 140, 141 },

        .success       = { 46, 204, 113 },
        .warning       = { 241, 196, 15 },
        .error         = { 231, 76, 60 },
        .info          = { 52, 152, 219 }
    }
};



void setTheme(ThemeID id) {
    currentTheme = id;
}

ThemeID getTheme() {
    return currentTheme;
}

void listNamesThemes(char *names[]) {
    names[THEME_DEFAULT] = "Default";
}