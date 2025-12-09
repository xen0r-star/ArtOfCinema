#include "theme.h"

ThemeID currentTheme = THEME_DEFAULT;
Theme THEMES[] = {
    [THEME_DEFAULT] = {
        .primary       = {  19, 213,  12 },
        .secondary     = { 255, 255, 255 },
        .tertiary      = {   4, 184, 229 },
        .background    = { 236, 240, 241 },

        .text          = { 255, 255, 255 },
        .textSecondary = {  71,  71,  71 },

        .success       = {  19, 161,  14 },
        .warning       = { 179,   0,  21 },
        .error         = { 197,  15,  31 },
        .info          = { 217, 156,   0 }
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