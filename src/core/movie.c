#include "movie.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static MovieNode *movieListMain = NULL;
static MovieNode *movieListTemp = NULL;

int loadMovies() {
    FILE *file = fopen("data/movies.dat", "r");
    if (file == NULL) return -1;

    int id, duration, type_count, note, year, cast_count;
    char name[100], typesStr[512], desc[512], director[100], age[10], lang[50], castStr[512];
    MovieNode *tail = NULL;

    while (fscanf(file, "%5d;%99[^;];%3d;%2d;%511[^;];%3d;%511[^;];%4d;%99[^;];%9[^;];%49[^;];%2d;%511[^\n]\n",
            &id, name, &duration, &type_count, typesStr, &note,
            desc, &year, director, age, lang, &cast_count, castStr) == 13) {
        
        Movie *newMovie = calloc(1, sizeof(Movie));

        newMovie->id = id;
        newMovie->name = strdup(name);
        newMovie->duration = duration;
        newMovie->type_count = type_count;
        newMovie->note = note;
        newMovie->year = year;
        newMovie->cast_count = cast_count;
        newMovie->description = strdup(desc);
        newMovie->director = strdup(director);
        newMovie->ageRating = strdup(age);
        newMovie->language = strdup(lang);


        // Parse Types
        if (newMovie->type_count > 0) {
            newMovie->types = malloc(sizeof(char*) * newMovie->type_count);
            char *token = strtok(typesStr, "|");
            for (int i = 0; i < newMovie->type_count && token; i++) {
                newMovie->types[i] = strdup(token);
                token = strtok(NULL, "|");
            }

        } else {
            newMovie->types = NULL;
        }

        // Parse Cast
        if (newMovie->cast_count > 0) {
            newMovie->cast = malloc(sizeof(char*) * newMovie->cast_count);
            char *token = strtok(castStr, "|");
            for (int i = 0; i < newMovie->cast_count && token; i++) {
                newMovie->cast[i] = strdup(token);
                token = strtok(NULL, "|");
            }
            
        } else {
            newMovie->cast = NULL;
        }


        // Create and append Node
        MovieNode *newNode = malloc(sizeof(MovieNode));
        if (newNode) {
            newNode->movie = newMovie;
            newNode->next = NULL;

            if (movieListMain == NULL) {
                movieListMain = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    fclose(file);
    return 0;
}

void deleteMovie(void *movie){
    Movie *mv = movie; 
    // FILE *file = fopen("data/movies.dat", "r"); ⚠️ SUPPR DANS FILES A FAIRE
    // if (file == NULL) return -1;

    if (mv == NULL) return;

    int targetId = mv->id;

    MovieNode *current = movieListMain;
    MovieNode  *prev = NULL;

    while (current != NULL) {
        if (current->movie->id == targetId) {
            if (prev == NULL) {
                movieListMain = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;

        }
        prev = current;
        current = current->next;
    }
    cursor(2, 2);
    printf("Le film avec ID %d n'a pas été trouvé dans la liste chainée.", targetId);
    Sleep(3000);
    // fclose(file);
    return;
}


MovieNode* getMovieList() {
    return movieListMain;
}

Movie* getMovieById(int id) {
    MovieNode *current = movieListMain;
    while (current != NULL) {
        if (current->movie->id == id) {
            return current->movie;
        }
        current = current->next;
    }
    return NULL;
}

int searchMovieByName(const char *movieName, const char *search) {
    if (!search || strlen(search) == 0) return 1;
    if (!movieName) return 0;

    char h[512], n[512];
    strncpy(h, movieName, 511); 
    h[511] = 0;
    
    strncpy(n, search, 511); 
    n[511] = 0;

    for(int i = 0; h[i]; i++) h[i] = tolower(h[i]);
    for(int i = 0; n[i]; i++) n[i] = tolower(n[i]);

    return strstr(h, n) != NULL;
}