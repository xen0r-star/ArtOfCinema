#include "credit.h"

void showCreditPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);


    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 10);
    Sleep(1500);
    clearScreen();


    createText(ALIGN_CENTER, ALIGN_MIDDLE, "Coded by", PRIMARY_COLOR);

    Sleep(1000);
    clearScreen();


    createText(ALIGN_CENTER, ALIGN_MIDDLE, "Xen0r-star & TomusLeVrai", PRIMARY_COLOR);

    Sleep(1000);
    clearScreen();



    for (int i = rows + 35; i >= -5; i--) {
        // createText(ALIGN_CENTER, i - 82, "=== EQUIPE PRINCIPALE ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 81, "Coded by............................... Xen0r-Star & TomusLeVrai                  ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 80, "Optimisation random.................... TomusLeVrai                               ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 79, "Corrections tardives................... Xen0r-Star a 3h du matin                  ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 78, "Gestion des snacks..................... TomusLeVrai (et son paquet de chips sacre)", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 76, "=== RECHERCHE & DEVELOPPEMENT ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 75, "Xen0r-Star............................ Meilleur dev auto-proclame      ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 74, "Le mouton _JEB........................ Directeur du departement couleur", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 73, "Le Chat Assis sur le Clavier.......... Redaction involontaire de code  ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 72, "CIO KOMBUCHA.......................... Expert en boissons fermentees   ", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 70, "=== TEST ET VALIDATION ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 69, "Pingouin Depressif.................... Testeur moral douteux               ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 68, "TomusLeVrai........................... Signaleur de bugs qui n'existent pas", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 67, "Clavier Possede....................... Declencheur de bugs spontanes       ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 66, "La Fourchette Fantome................. Verificatrice officielle des pates  ", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 64, "=== SUPPORT TECHNIQUE ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 63, "J'ai Faim............................. Responsable des pauses dejeuner           ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 62, "Un Daltonien.......................... Expert en reconnaissance de couleurs      ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 61, "UltraLowLatency....................... Responsable des reponses avant la question", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 60, "Kameto................................ Reponse de la France: NON                 ", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 58, "=== EVENEMENTS HISTORIQUES ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 57, "Chips consommees...................... +/-42 paquets par TomusLeVrai          ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 56, "Lignes de code supprimees............. Beaucoup trop                          ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 55, "Lignes de code ctrl+c................. Beaucoup trop                          ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 54, "Lignes de code ctrl+v................. Beaucoup trop                          ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 53, "Moments de panique.................... Statistiques inaccessibles             ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 52, "Heures de sommeil sacrifiees.......... (information supprimee pour votre bien)", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 50, "=== CONTRIBUTIONS ANONYMES ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 49, "L'homme du Rif........................ Homosexuel anonyme", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 48, "Root2................................. Ban du disocrd ?  ", TERTIARY_COLOR);

        // createText(ALIGN_CENTER, i - 46, "=== REMERCIEMENTS SPeCIAUX ===", PRIMARY_COLOR);
        // createText(ALIGN_CENTER, i - 45, "Aux bugs.............................. Pour leur persistance admirable  ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 44, "A notre clavier....................... Defunt mais honore               ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 43, "A notre ecrant........................ Defunt mais honore               ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 42, "A notre sourit........................ Defunt mais honore               ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 41, "A la vie.............................. Pour nous rappeler la sauvegarde ", TERTIARY_COLOR);
        // createText(ALIGN_CENTER, i - 40, "Et a vous............................. Pour avoir laisse defiler tout ca", TERTIARY_COLOR);



        createText(ALIGN_CENTER, i - 30, "__  __           ___               _             ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 29, "\\ \\/ /___ _ __  / _ \\ _ __     ___| |_ __ _ _ __ ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 28, " \\  // _ \\ '_ \\| | | | '__|___/ __| __/ _` | '__|", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 27, " /  \\  __/ | | | |_| | | |____\\__ \\ || (_| | |   ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 26, "/_/\\_\\___|_| |_|\\___/|_|      |___/\\__\\__,_|_|   ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 25, "Github: https://github.com/xen0r-star", TERTIARY_COLOR);


        createText(ALIGN_CENTER, i - 8, " _____                           _____                   ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 7, "|_   _|                         /  __ \\                  ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 6, "  | | ___  _ __ ___  _   _ ___  | /  \\/ ___  _ __ _ __   ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 5, "  | |/ _ \\| '_ ` _ \\| | | / __| | |    / _ \\| '__| '_ \\  ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 4, "  | | (_) | | | | | | |_| \\__ \\ | \\__/\\ (_) | |  | |_) | ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 3, "  \\_/\\___/|_| |_| |_|\\__,_|___/  \\____/\\___/|_|  | .__( )", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 2, "                                                | |     ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 1, "                                                |_|     ", PRIMARY_COLOR);
        createText(ALIGN_CENTER, i - 1, "Github: https://github.com/TomusLeVrai", TERTIARY_COLOR);

        
        Sleep(400);
        clearScreen();
        i--;
    }
    clearScreen();
    Sleep(500);


    setCurrentPage(PAGE_SETTINGS);
}