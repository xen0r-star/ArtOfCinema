#include "main.h"



int main() {
    SetConsoleTitle("Art Of Cinema - Terminal Edition");
    hideCursor();

    int columns, rows, previousColumns = 0, previousRows = 0;
    AppPage page = PAGE_LOADING, previousPage = -1;

    while(1) {
        // Recuperer la taille de l'écran
        sizeScreen(&columns, &rows);

        // Si taille change OU changement de page
        if (columns != previousColumns || rows != previousRows || page != previousPage) {
            previousPage = page;

            switch (page) {
                case PAGE_LOADING:
                    page = showLoadingScreen();
                    break;
                case PAGE_HOME:
                    page = showHomePage();
                    break;
                case PAGE_LOGIN:
                    page = showHomePage();
                    break;
                case PAGE_VALIDE_LOGIN:
                    page = showHomePage();
                    break;
                case PAGE_NVALIDE_LOGIN:
                    page = showHomePage();
                    break;
                case PAGE_SIGNUP:
                    page = showHomePage();
                    break;
                case PAGE_VALIDE_SIGNUP:
                    page = showHomePage();
                    break;
                case PAGE_DIRECTOR:
                    page = showHomePage();
                    break;
                case PAGE_DIRECTOR_FILM:
                    page = showHomePage();
                    break;
                case PAGE_DIRECTOR_SHOP:
                    page = showHomePage();
                    break;
                case PAGE_CLIENT:
                    page = showHomePage();
                    break;
                case PAGE_EXIT: 
                    return;
            }
            // OUI GLOBAL C BIEN MAIS EN #C C POSSIBLE ?
            // Comme la variable buttons dans le fichier button.c
            // la mettre tout en haut des methode et lui faire une methode qui la retourne
            // getPage() un bail du genre
            // sur l'exemple j'ai vu il utilise juste une fct qui get une variable d'un fichier.c,
            //  et la fct est accessible partout donc il considere la variable comme "global", 

            // LAISSONS LES COMMENTAIRES COMME CECI, MOI JDOIS TAILLER c'est CIAO
            
            // Met a jour les anciennes valeurs
            previousColumns = columns;
            previousRows = rows;
        }

        // Gere les evenements (ne redessine pas la page)
        // On appelle seulement inputEvent qui gère aussi les clicks généraux
        event();
        
        // Petite pause pour ne pas surcharger le CPU
        Sleep(10);
    }
    

    return 0;
}