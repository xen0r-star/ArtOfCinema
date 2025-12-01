#ifndef TRANSLATION_H
#define TRANSLATION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"

#define TABLE_SIZE 1024  // Taille de table de traductions (Taille maximale)


typedef struct Translation{
    char* key;
    char* value;
    struct Translation* next;   // Permet de gérer les collisions
} Translation;

typedef struct{
    const char* lang;
    Translation* table[TABLE_SIZE];
} TranslationTable;


void initTranslation();
void setLanguage(const char* langue);
const char* getLanguage();
const char* _T(const char* key);

#endif