#include "translation.h"

TranslationTable languages[2];  // languages[N] : N soit le nombres de langues disponible dans le programme
const char* language = "fr";    // Langues par défaut : français

// Algorithme de hash djb2
static unsigned long hash(const char* str) {    // Transformation de key en hash pour stockage rapide table O(1)
    unsigned long hash = 5381;
    int c;  // Va permettre de stocker tout les caractères de la key 

    while((c = *str++)) // Parcourt de toute la key jusqu'au caractères d'échappement « \0 » | *str caractère actuel | str++ avance au prochain caractère
        hash = ((hash << 5) + hash) + c;    // Transformation de chaque caractère en hash : hash * 33 + c | Pourquoi cela ? Pour que même si deux clés ont un caractère de différences le hash sera très différent pour éviter les collisions dans la table (33 : car crée un très bon mélange de bit et une facilité de calcul)
        
    return hash % TABLE_SIZE;   // Connaître dans quel index stocker la key grâce au hash
}

// Libération de toute la mémoire dynamique des traductions. Exemple : languages[][] = NULL
static void resetTranslation(TranslationTable* table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        Translation* entry = table->table[i];
        while(entry) {   // Parcourt jusqu'à « NULL »
            Translation* tmp = entry;
            entry = entry->next;
            free(tmp->key); // Libération allocation dynamique mémoire pour key
            free(tmp->value);
            free(tmp);
        }
    }
}

static void addTranslation(TranslationTable* translationTblPrev, const char* key, const char* value) {  // Ajout d'une traduction quelconques
    if(!key || !value) return;

    unsigned long hashID = hash(key);   // Récupération d'un hash (plus facile pour le stockage). Exemple : laoding -> 125
    Translation* newTranslation = malloc(sizeof(Translation));  // Allocation d'un nouvel espace en mémoire (Réservation) et création de la table de traduction
    newTranslation->key = strdup(key);  // Allocation + copie de key dans la table de la nouvelle traduction (Copie). Exemple : copie de 'x' dans newTranslation
    newTranslation->value = strdup(value);
    newTranslation->next = translationTblPrev->table[hashID];   // Ajout à la nouvelle traduction de la table de traduction précédente | Exemple : translationTblPrev[] → [A] → [B] → [NULL] ⇒ [newTranslation] → [A] → [B] → [NULL]
    translationTblPrev->table[hashID] = newTranslation; // permet que l'ancien tableau deviennent la nouvelle tête de liste. Exemple : translationTblPrev[] → [newTranslation] → [A] → [B] → [NULL]
}


void initTranslation() { // Initialisation des tables stocker les traductions
    // Initialisation
    languages[0].lang = "fr";   // Déclaration tableau traduction langue française
    memset(languages[0].table, 0, sizeof(languages[0].table));  // permet de remplir la table[0] de 0/NULL. Exemple : languages[0] = {0} / languages[0] = {NULL}
    languages[1].lang = "en";   // Déclaration tableau traduction langue anglaise
    memset(languages[1].table, 0, sizeof(languages[1].table));
    
    //  Chargement du fichier CSV
    loadCSVFile("i18n/translations.csv");
}

static void loadCSVFile(const char* fileName) { // Chargement du fichier CSV contenant toutes les traductions
    FILE *f = fopen(fileName, "r");
    if(!f) return;

    char line[1024];
    fgets(line, sizeof(line), f);   // Ignore le header. Exemple : welcome, loading

    while(fgets(line, sizeof(line), f)) {
        char *key = strtok(line, ",");
        char *fr = strtok(NULL, ",");
        char *en = strtok(NULL, "\r\n");

        if(!key || !fr || !en) continue;

        key[strcspn(key, "\r\n")] = 0;
        key[strcspn(key, "\r\n")] = 0;
        key[strcspn(key, "\r\n")] = 0;

        addTranslation(&languages[0], key, fr);
        addTranslation(&languages[1], key, en);
    }

    fclose(f);
}


void setLanguage(const char* langue) {
    if(!langue) return;
    for(int i = 0; i < 2; i++) {
        if(strcmp(languages[i].lang, langue) == 0) {
            language = languages[i].lang;
            return;
        }
    }
}

const char* getLanguage() {
    if (language) {
        return language;
    }
}


const char* _T(const char* key) {    // Lookup dans les tables de traductions via une key. Exemple : languages["LANGUE"]["CLE"] → TEXTE
    TranslationTable* table = NULL; // Initialisation du tableau et parcourt pour trouver la bonne langue dans le tableau. Exemple : languages["LANGUE"]
    for(int i = 0; i < 2; i++) {
        if(strcmp(languages[i].lang, language) == 0) {
            table = &languages[i];
            break;
        }
    }
    
    if(!table) return key;  // Si aucune table alors est retourner la key donné en argument

    unsigned long hashID = hash(key);   // Calcul l'index de la clé (0 juque TABLE_SIZE - 1)
    Translation* entry = table->table[hashID];  // Récupération de la liste à l'index key

    while(entry) {   // Parcourt de la liste pour trouver la bonne traduction
        if(strcmp(entry->key, key) == 0)    // Si l'index key actuel correspond à celui de la key demandé
            return entry->value;    // Retourne la valeur de la key souhaité
        entry = entry->next;    // Passage au prochain index
    }
    return "Erreur de traduction/Error of translate";    // Si non trouvé, on retourne une erreur de traduction
}