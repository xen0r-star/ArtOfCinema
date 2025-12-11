#include "settings.h"

static SettingTab currentTab = SETTING_GLOBAL;

static void globalTab(){
    currentTab = SETTING_GLOBAL;
    setCurrentPage(PAGE_SETTINGS);
}

static void languagesTab(){
    currentTab = SETTING_LANGUAGES;
    setCurrentPage(PAGE_SETTINGS);
}

static void displayTab(){
    currentTab = SETTING_DISPLAY;
    setCurrentPage(PAGE_SETTINGS);
}


static void closeSettings() {
    setCurrentPage(getSavePage());
}


static void logout() {
    resetUser();
    setCurrentPage(PAGE_LOGIN);
}

static void changeLanguage(void *data) {
    const char* language = (const char*)data;
    setLanguage(language);
    refreshPage();
}

static void changeTheme(void *data) {
    const ThemeID theme = (ThemeID)data;
    setTheme(theme);
    refreshPage();
}



void showSettingsPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();


    int width = 70;
    int x = (columns - width) / 2;
    int y = 10;

    Button btn1 = {
        x, y + 2, width / 3, 
        currentTab == SETTING_GLOBAL ? TERTIARY_COLOR : SECONDARY_COLOR, 
        STYLE_BORDERLESS, _T("setting.menu.o1"), globalTab
    };
    Button btn2 = {
        x + width / 3, y + 2, width / 3, 
        currentTab == SETTING_LANGUAGES ? TERTIARY_COLOR : SECONDARY_COLOR, 
        STYLE_BORDERLESS, _T("setting.menu.o2"), languagesTab
    };
    Button btn3 = {
        x + 2 * (width / 3), y + 2, width / 3, 
        currentTab == SETTING_DISPLAY ? TERTIARY_COLOR : SECONDARY_COLOR, 
        STYLE_BORDERLESS, _T("setting.menu.o3"), displayTab
    };

    createMenu(x, y, width, PRIMARY_COLOR, STYLE_DEFAULT, "setting.menu.label", &btn1, &btn2, &btn3);

    createButton(columns - 20, rows - 3, 20, _T("setting.btn.close"), SECONDARY_COLOR, STYLE_DEFAULT, closeSettings);



    if (currentTab == SETTING_GLOBAL) {
        createButton(
            x + 4, y + 5, 20, _T("logout.btn.dec"), 
            WARNING_COLOR, STYLE_DEFAULT, logout
        );

    } else if (currentTab == SETTING_LANGUAGES) {
        createDataButton(
            x + 4, y + 5, 20, _T("setting.language.french"), 
            !strcmp(getLanguage(), "fr") ? TERTIARY_COLOR : SECONDARY_COLOR, 
            STYLE_DEFAULT, changeLanguage, "fr"
        );
        createDataButton(
            x + 25, y + 5, 20, _T("setting.language.english"), 
            !strcmp(getLanguage(), "en") ? TERTIARY_COLOR : SECONDARY_COLOR, 
            STYLE_DEFAULT, changeLanguage, "en"
        );

    } else if (currentTab == SETTING_DISPLAY) {
        createDataButton(
            x + 4, y + 5, 20, _T("setting.theme.default"), 
            getTheme() == THEME_DEFAULT ? TERTIARY_COLOR : SECONDARY_COLOR, 
            STYLE_DEFAULT, changeTheme, (void*) THEME_DEFAULT
        );
        createDataButton(
            x + 25, y + 5, 20, _T("setting.theme.girly"), 
            getTheme() == THEME_GIRLY ? TERTIARY_COLOR : SECONDARY_COLOR, 
            STYLE_DEFAULT, changeTheme, (void*) THEME_GIRLY
        );
    }
}