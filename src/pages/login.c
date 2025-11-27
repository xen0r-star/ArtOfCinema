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


void validEmail() {
    const char *emailUser = getInput(0)->value;

    if (isValidEmail(emailUser)) {
        strcpy(user.email, emailUser);
        setCurrentPage(PAGE_LOGIN);

    } else {
        createText(5 , 13, "Email invalide" , COLOR_RED, CENTER);
    }
}


void signIn() {
    const char *password = getInput(0)->value;

    user.role = checkLogin(user.email, password);
    user.logged = 1;
    setCurrentPage(PAGE_LOGIN);
}


void nextStepSignUp() {
    const char *password = getInput(0)->value;
    const char *confirmPassword = getInput(1)->value;

    if (strcmp(password, "") != 0 && strcmp(confirmPassword, "") != 0) {
        if (strcmp(password, confirmPassword) == 0) {
            saveUserCredentials(user.email, password);
            user.logged = 1;
            setCurrentPage(PAGE_LOGIN);

        } else {
            createText(5 , 12, "Le mots de passe ne correspondent pas", COLOR_RED, CENTER);
        }
    }
}

void signUp() {
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

    createText(5, 10, "Votre Compte ARTOFCINEMA", COLOR_GREEN, CENTER);


    if (strcmp(user.email, "") == 0) {
        createText(5 , 11, "Entrez votre email pour vous connecter ou creer un compte", COLOR_WHITE, CENTER);
        
        createInput((columns - INPUT_WIDTH) / 2, 15, "Email", "exemple@artofcinema.be");
        createButton((columns - 21) / 2, rows - 7, 18, COLOR_GREEN, "CONTINUER", validEmail);

    } else if (!user.logged) {
        createText(5 , 13, user.email, COLOR_BRIGHT_BLACK, CENTER); 

        if (emailExiste(user.email) == STATUS_FOUND) {
            createText(5 , 11, "Connecter-vous à votre compte", COLOR_WHITE, CENTER);
            createInput((columns - INPUT_WIDTH) / 2, 15, "Mot de passe", "Votre mot de passe");
            createButton((columns - 21) / 2, rows - 7, 18, COLOR_GREEN, "Connexion", signIn);
            
        } else {
            createText(5 , 11, "Créer votre compte", COLOR_WHITE, CENTER);
            createInput((columns - INPUT_WIDTH) / 2, 15, "Mot de passe", "Votre mot de passe");
            createInput((columns - INPUT_WIDTH) / 2, 18, "Confirmer le mot de passe", "Votre mot de passe");
            createButton((columns - 21) / 2, rows - 7, 21, COLOR_GREEN, "Suivant", nextStepSignUp);
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
                createText(5 , 11, "Identiant de connexion non valide", COLOR_RED, CENTER);
                createText(5 , 15, user.email, COLOR_BRIGHT_BLACK, CENTER);
                createText(5 , 18, "**************", COLOR_BRIGHT_BLACK, CENTER);
                createButton((columns - 21) / 2, rows - 7, 21, COLOR_WHITE, "Retour", backToLogin);
                break;

            case ROLE_NONE:
                createText(5 , 11, "Créer votre compte", COLOR_WHITE, CENTER);
                createInput((columns - INPUT_WIDTH) / 2, 15, "Nom", "Votre nom");
                createInput((columns - INPUT_WIDTH) / 2, 18, "Prenom", "Votre prénom");
                createButton((columns - 21) / 2, rows - 7, 21, COLOR_GREEN, "S'inscrire", signUp);
                break;
        }
    }
}