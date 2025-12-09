#include "login.h"


static User user = {
    .logged = 0,
    .role = ROLE_NONE,
    .email = ""
};

void resetUser() {
    user = (User) {
        .logged = 0,
        .role = ROLE_NONE,
        .email = ""
    };
}


static void validEmail() {
    const char *emailUser = getInput(0)->value;

    if (isValidEmail(emailUser)) {
        strcpy(user.email, emailUser);
        setCurrentPage(PAGE_LOGIN);

    } else {
        createText(ALIGN_CENTER, 13, _T("login.inv.mail"), ERROR_COLOR);
    }
}


static void signIn() {
    const char *password = getInput(0)->value;

    user.role = checkLogin(user.email, password);
    user.logged = 1;
    setCurrentPage(PAGE_LOGIN);
}


static void nextStepSignUp() {
    const char *password = getInput(0)->value;
    const char *confirmPassword = getInput(1)->value;

    if (strcmp(password, "") != 0 && strcmp(confirmPassword, "") != 0) {
        if (strcmp(password, confirmPassword) == 0) {
            saveUserCredentials(user.email, password);
            user.logged = 1;
            setCurrentPage(PAGE_LOGIN);
          
        } else {
            createText(ALIGN_CENTER , 12, _T("login.crt.acc.ipt.inv.pswd"), ERROR_COLOR);
        }
    }
}

static void signUp() {
    const char *name = getInput(0)->value;
    const char *surname = getInput(1)->value;

    if (strcmp(name, "") != 0 && strcmp(surname, "") != 0) {
        setName(user.email, name);
        setSurname(user.email, surname);

        user.role = ROLE_CLIENT;
        setCurrentPage(PAGE_LOGIN);
    }
}


static void backToLogin() {
    resetUser();
    setCurrentPage(PAGE_LOGIN);
}



void showLoginPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);
    drawFooter();
    buttonLanguage();
    buttonSetting();

    createText(ALIGN_CENTER, 10, _T("login.visual.text"), PRIMARY_COLOR);


    if (strcmp(user.email, "") == 0) {
        createText(ALIGN_CENTER, 11, _T("login.ipt.mail"), TEXT_COLOR);
        
        createInput(ALIGN_CENTER, 15, _T("login.mail"), _T("login.mail.expl"));
        createButton(ALIGN_CENTER, rows - 7, 18, _T("login.btn.nxt"), PRIMARY_COLOR, STYLE_DEFAULT, validEmail);

    } else if (!user.logged) {
        createText(ALIGN_CENTER, 13, user.email, TEXTSECONDARY_COLOR); 

        if (emailExiste(user.email) == STATUS_FOUND) {
            createText(ALIGN_CENTER, 11, _T("login.acc.conn"), TEXT_COLOR);
            createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.label"), _T("login.crt.acc.ipt.placeholder"));
            createButton(ALIGN_CENTER, rows - 7, 18, _T("login.btn.conn"), PRIMARY_COLOR, STYLE_DEFAULT, signIn);
            
        } else {
            createText(ALIGN_CENTER, 11, _T("login.crt.acc"), TEXT_COLOR);
            createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.label"), _T("login.crt.acc.ipt.placeholder"));
            createInput(ALIGN_CENTER, 18, _T("login.crt.acc.ipt.cnfrmpswd"), _T("login.crt.acc.ipt.placeholder"));
            createButton(ALIGN_CENTER, rows - 7, 21, _T("login.btn.crt.acc.next"), PRIMARY_COLOR, STYLE_DEFAULT, nextStepSignUp);
        }

    } else if (user.logged) {
        switch (user.role) {
            case ROLE_CLIENT:
                setCurrentPage(PAGE_CLIENT);
                break;
            
            case ROLE_DIRECTOR:
                setCurrentPage(PAGE_DIRECTOR);
                break;
            
            case ROLE_ERROR:
                createText(ALIGN_CENTER, 11, _T("login.acc.conn.visual.txt.err"), ERROR_COLOR);
                createText(ALIGN_CENTER, 15, user.email, TEXTSECONDARY_COLOR);
                createText(ALIGN_CENTER, 18, "**************", TEXTSECONDARY_COLOR);
                createButton(ALIGN_CENTER, rows - 7, 21, _T("return"), SECONDARY_COLOR, STYLE_DEFAULT, backToLogin);
                break;

            case ROLE_NONE:
                createText(ALIGN_CENTER, 11, _T("login.crt.acc"), TEXT_COLOR);
                createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.labname"), _T("login.crt.acc.ipt.phname"));
                createInput(ALIGN_CENTER, 18, _T("login.crt.acc.ipt.labfname"), _T("login.crt.acc.ipt.phfname"));
                createButton(ALIGN_CENTER, rows - 7, 21, _T("login.crt.acc.btn"), PRIMARY_COLOR, STYLE_DEFAULT, signUp);
                break;
        }
    }
}