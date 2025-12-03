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
        createText(ALIGN_CENTER, 13, _T("login.inv.mail"), COLOR_RED);
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
            createText(ALIGN_CENTER , 12, _T("login.crt.acc.ipt.inv.pswd"), COLOR_RED);
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

    createText(ALIGN_CENTER, 10, _T("login.visual.text"), COLOR_GREEN);


    if (strcmp(user.email, "") == 0) {
        createText(ALIGN_CENTER, 11, _T("login.ipt.mail"), COLOR_WHITE);
        
        createInput(ALIGN_CENTER, 15, _T("login.mail"), _T("login.mail.expl"));
        createButton(ALIGN_CENTER, rows - 7, 18, COLOR_GREEN, _T("login.btn.nxt"), validEmail);

    } else if (!user.logged) {
        createText(ALIGN_CENTER, 13, user.email, COLOR_BRIGHT_BLACK); 

        if (emailExiste(user.email) == STATUS_FOUND) {
            createText(ALIGN_CENTER, 11, _T("login.acc.conn"), COLOR_WHITE);
            createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.label"), _T("login.crt.acc.ipt.placeholder"));
            createButton(ALIGN_CENTER, rows - 7, 18, COLOR_GREEN, _T("login.btn.conn"), signIn);
            
        } else {
            createText(ALIGN_CENTER, 11, _T("login.crt.acc"), COLOR_WHITE);
            createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.label"), _T("login.crt.acc.ipt.placeholder"));
            createInput(ALIGN_CENTER, 18, _T("login.crt.acc.ipt.cnfrmpswd"), _T("login.crt.acc.ipt.placeholder"));
            createButton(ALIGN_CENTER, rows - 7, 21, COLOR_GREEN, _T("login.btn.crt.acc.next"), nextStepSignUp);
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
                createText(ALIGN_CENTER, 11, _T("login.acc.conn.visual.txt.err"), COLOR_RED);
                createText(ALIGN_CENTER, 15, user.email, COLOR_BRIGHT_BLACK);
                createText(ALIGN_CENTER, 18, "**************", COLOR_BRIGHT_BLACK);
                createButton(ALIGN_CENTER, rows - 7, 21, COLOR_WHITE, _T("login.acc.conn.visual.txt.err.bck"), backToLogin);
                break;

            case ROLE_NONE:
                createText(ALIGN_CENTER, 11, _T("login.crt.acc"), COLOR_WHITE);
                createInput(ALIGN_CENTER, 15, _T("login.crt.acc.ipt.labname"), _T("login.crt.acc.ipt.phname"));
                createInput(ALIGN_CENTER, 18, _T("login.crt.acc.ipt.labfname"), _T("login.crt.acc.ipt.phfname"));
                createButton(ALIGN_CENTER, rows - 7, 21, COLOR_GREEN, _T("login.crt.acc.btn"), signUp);
                break;
        }
    }
}