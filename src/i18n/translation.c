#include "translation.h"


TranslationTable translation[2];
const char* selectLanguage = "fr";

static unsigned long hash(const char* str) {
    /* Transform la clé en hash (nombre) pour optimiser la recherche dans la table de traduction
    *  Algorithme de hash djb2
    */
    unsigned long hash = 5381;
    int c;

    /*
    *  Parcourt de toute la cle jusqu'au caractères d'échappement « \0 »
    *  Transformation de chaque caractère en hash : hash * 33 + c
    *  Pourquoi cela ? Pour que même si deux clés ont un caractère de différences le hash sera très différent 
    *  pour éviter les collisions dans la table (33 : car crée un très bon mélange de bit et une facilité de calcul)
    */
    while((c = *str++))
        hash = ((hash << 5) + hash) + c;
        
    return hash % TABLE_SIZE;
}

static void resetTranslation(TranslationTable* table) __attribute__((unused));
static void resetTranslation(TranslationTable* table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        Translation* entry = table->table[i];
        while(entry) {
            Translation* tmp = entry;
            entry = entry->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }
}

static void addTranslation(TranslationTable* translationTblPrev, const char* key, const char* value) {
    if(!key || !value) return;

    unsigned long hashID = hash(key);
    Translation* newTranslation = malloc(sizeof(Translation));
    newTranslation->key = strdup(key);
    newTranslation->value = strdup(value);
    newTranslation->next = translationTblPrev->table[hashID];
    translationTblPrev->table[hashID] = newTranslation;
}

static void loadCSVFile(const char* fileName) {
    FILE *f = fopen(fileName, "r");
    if(!f) return;

    char line[1024];
    fgets(line, sizeof(line), f);   // Ignore le header

    while(fgets(line, sizeof(line), f)) {
        char *key = strtok(line, ",");
        char *fr = strtok(NULL, ",");
        char *en = strtok(NULL, "\r\n");

        if(!key || !fr || !en) continue;

        key[strcspn(key, "\r\n")] = 0;
        key[strcspn(key, "\r\n")] = 0;
        key[strcspn(key, "\r\n")] = 0;

        addTranslation(&translation[0], key, fr);
        addTranslation(&translation[1], key, en);
    }

    fclose(f);
}

void initTranslation() {
    translation[0].lang = "fr";
    memset(translation[0].table, 0, sizeof(translation[0].table));
    translation[1].lang = "en";
    memset(translation[1].table, 0, sizeof(translation[1].table));
    
    loadCSVFile("i18n/translations.csv");
}


void setLanguage(const char* langue) {
    if(!langue) return;

    for(int i = 0; i < 2; i++) {
        if(strcmp(translation[i].lang, langue) == 0) {
            selectLanguage = translation[i].lang;
            return;
        }
    }
}

const char* getLanguage() {
    return selectLanguage;
}


const char* _T(const char* key) {
    TranslationTable* table = NULL;
    for(int i = 0; i < 2; i++) {
        if(strcmp(translation[i].lang, selectLanguage) == 0) {
            table = &translation[i];
            break;
        }
    }
    
    if(!table) return key;

    unsigned long hashID = hash(key);
    Translation* entry = table->table[hashID];

    while(entry) {
        if(strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }

    return "Error of translate";
}