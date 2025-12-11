#ifndef THEME_H
#define THEME_H


#include "../utils/color.h"

#define THEME_COUNT 2
typedef enum ThemeID {
    THEME_DEFAULT,
    THEME_GIRLY
} ThemeID;


typedef struct Theme {
    ColorRGB primary;
    ColorRGB secondary;
    ColorRGB tertiary;
    ColorRGB background;

    ColorRGB text;
    ColorRGB textSecondary;

    ColorRGB success;
    ColorRGB warning;
    ColorRGB error;
    ColorRGB info;
} Theme;


extern ThemeID currentTheme;
extern Theme THEMES[THEME_COUNT];

#define PRIMARY_COLOR       (THEMES[currentTheme].primary)
#define SECONDARY_COLOR     (THEMES[currentTheme].secondary)
#define TERTIARY_COLOR      (THEMES[currentTheme].tertiary)
#define BACKGROUND_COLOR    (THEMES[currentTheme].background)

#define TEXT_COLOR          (THEMES[currentTheme].text)
#define TEXTSECONDARY_COLOR (THEMES[currentTheme].textSecondary)

#define SUCCESS_COLOR       (THEMES[currentTheme].success)
#define WARNING_COLOR       (THEMES[currentTheme].warning)
#define ERROR_COLOR         (THEMES[currentTheme].error)
#define INFO_COLOR          (THEMES[currentTheme].info)


void setTheme(ThemeID theme);
ThemeID getTheme();
void listNamesThemes(char *names[]);


#endif