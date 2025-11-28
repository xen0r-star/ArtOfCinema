#ifndef TRANSLATION_H
#define TRANSLATION_H
#define TABLE_SIZE 1024  // Taille de table de traductions (Taille maximale)


#include "../main.h"


typedef struct Translation{
    char* key;
    char* value;
    struct Translation* next;   // Permet de gérer les collisions
} Translation;

typedef struct{
    const char* lang;
    Translation* table[TABLE_SIZE];
} TranslationTable;


unsigned long hash(const char* str);
void resetTranslation(TranslationTable* table);
void addTranslation(TranslationTable* translationTblPrev, const char* key, const char* value);
void initTranslation();
void loadCSVFile(const char* fileName);
void setLanguage(const char* langue);
const char* getLanguage();
const char* _T(const char* key);

#endif