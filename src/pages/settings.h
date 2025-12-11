#ifndef SETTINGS_H
#define SETTINGS_H


#include "../components/logo.h"
#include "../components/footer.h"
#include "../components/text.h"
#include "../components/input.h"
#include "../components/button.h"
#include "../components/menu.h"

#include "../types/user.h"
#include "../utils/color.h"

#include "../main.h"


typedef enum SettingTab {
    SETTING_GLOBAL,
    SETTING_LANGUAGES,
    SETTING_DISPLAY
} SettingTab;


void showSettingsPage();


#endif